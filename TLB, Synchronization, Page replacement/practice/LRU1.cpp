#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

// 노드 구조체
struct Node {
	int key;
	Node(int k) : key(k) {}
};

class LRUCache {
private:
	int capacity;
	// 이중 연결 리스트: key-value 쌍을 저장 (가장 최근 사용 순서)
	list<Node> cacheList;
	// 해시 맵: key와 해당 노드의 위치(iterator)를 매핑
	unordered_map<int, list<Node>::iterator> cacheMap;

public:
	LRUCache(int cap) : capacity(cap) {}

	void put(int key) {
		auto it = cacheMap.find(key);

		if (it != cacheMap.end()) {
			cout << "Cache Hit for key " << key << endl;
			it->second->key = key;
			cacheList.splice(cacheList.begin(), cacheList, it->second);
		}
		else {
			cout << "Page Fault for key " << key << endl;
			if (cacheList.size() == capacity) {
				int lastKey = cacheList.back().key;
				cout << "Cache is full. Evicting LRU key " << lastKey << endl;
				cacheList.pop_back();
				cacheMap.erase(lastKey);
			}
			cacheList.push_front(Node(key));
			cacheMap[key] = cacheList.begin();
		}
		cout << "Current Cache: [ ";
		for (const auto& node : cacheList) {
			cout << node.key << " ";
		}
		cout << "]" << endl;
		cout << "-----------------------------------------" << endl;
	}
};

int main() {
	LRUCache cache(2);

	cache.put(1);
	cache.put(2);
	cache.put(2);
	cache.put(3);
	cache.put(4);

	return 0;
}
