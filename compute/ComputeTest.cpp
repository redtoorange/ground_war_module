#include "ComputeTest.h"

#include "core/io/marshalls.h"
#include "core/io/resource_loader.h"
#include "servers/rendering_server.h"
#include "servers/rendering/rendering_device_binds.h"

void ComputeTest::_bind_methods() {
	ClassDB::bind_method(D_METHOD("loadComputeShader"), &ComputeTest::loadComputeShader);
}


PackedByteArray createPackedByteArray() {
	PackedByteArray pba;
	pba.resize(64);
	uint8_t *ptr = pba.ptrw();

	for (int i = 0; i < 16; i++) {
		encode_float(2.0f, &ptr[i * 4]);
	}

	return pba;
}

void ComputeTest::loadComputeShader() {
	RenderingDevice *renderingDevice = RenderingServer::get_singleton()->create_local_rendering_device();

	Ref<RDShaderFile> shaderFile = ResourceLoader::load("res://compute_example.glsl");
	if (shaderFile.is_valid()) {
		Ref<RDShaderSPIRV> shaderSpirv = shaderFile->get_spirv();
		RID shader = renderingDevice->shader_create_from_spirv(shaderSpirv->get_stages());
		RID pipeline = renderingDevice->compute_pipeline_create(shader);

		if (pipeline.is_valid()) {
			PackedByteArray data = createPackedByteArray();
			RID storageBuffer = renderingDevice->storage_buffer_create(64, data);

			Vector<RD::Uniform> uniforms;

			RD::Uniform u;
			u.uniform_type = RD::UNIFORM_TYPE_STORAGE_BUFFER;
			u.binding = 0;
			u.ids.push_back(storageBuffer);
			uniforms.push_back(u);

			RID uniformSet = renderingDevice->uniform_set_create(uniforms, shader, 0);

			RD::ComputeListID computeList = renderingDevice->compute_list_begin();
			renderingDevice->compute_list_bind_compute_pipeline(computeList, pipeline);
			renderingDevice->compute_list_bind_uniform_set(computeList, uniformSet, 0);
			renderingDevice->compute_list_dispatch(computeList, 2, 1, 1);
			renderingDevice->compute_list_end();

			renderingDevice->submit();
			renderingDevice->sync();

			PackedByteArray returnData = renderingDevice->buffer_get_data(storageBuffer);
			for (int i = 0; i < 16; i++) {
				float f = decode_float(&returnData.ptrw()[i * 4]);
				print_line(rtos(f));
			}
		}
	}

}
