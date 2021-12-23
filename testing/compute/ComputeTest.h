#ifndef COMPUTE_TEST_H
#define COMPUTE_TEST_H

#include "core/object/ref_counted.h"

class ComputeTest : public RefCounted {
	GDCLASS(ComputeTest, RefCounted);

protected:
	static void _bind_methods();

private:
	void loadComputeShader();
};

#endif
