#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <queue>
#include <utility>

template <typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;

	/** Wrapper for the std priority queue */
	std::priority_queue<
		PQElement,
		std::vector<PQElement>,
		std::greater<PQElement>
	> elements;


	/** \brief Is the collection empty? */
	bool Empty() const {
		return elements.empty();
	}


	/**
	 * \param item Item to add to the Queue
	 * \param p_priority The priority of the item
	 */
	void Put(T item, priority_t p_priority) {
		elements.emplace(p_priority, item);
	}

	/** \brief Get and Pop the highest priority item from the queue	 */
	T Get() {
		T bestItem = elements.top().second;
		elements.pop();
		return bestItem;
	}
};

#endif
