#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

struct Node {
	int key;
	bool refBit;
	Node(int k) : key(k), refBit(true) {}
};

class ClockCache {
private:
	int capacity;
	// 원형 연결 리스트
	list<Node> cacheList;
	// 해시 맵: key와 노드 위치(iterator)를 매핑
	unordered_map<int, list<Node>::iterator> cacheMap;
	// 포인터
	list<Node>::iterator clockHand;

public:
	ClockCache(int cap) : capacity(cap) {
		if (capacity > 0) {
			clockHand = cacheList.begin();
		}
	}

	void put(int key) {
		auto it = cacheMap.find(key);

		if (it != cacheMap.end()) {
			cout << "Cache Hit for key " << key << endl;
			// 참조 비트만 1로 설정
			it->second->refBit = true;
		}
		else {
			cout << "Page Fault for key " << key << endl;
			if (cacheList.size() == capacity) {
				while (true) {
					// 포인터가 마지막을 가리키면 처음으로 이동 (원형)
					if (clockHand == cacheList.end()) {
						clockHand = cacheList.begin();
					}

					if (clockHand->refBit) {
						// 참조 비트가 1이면 0으로 바꾸고 다음 페이지로 이동
						clockHand->refBit = false;
						cout << "  Key " << clockHand->key << " has refBit 1. Changing to 0 and checking next." << endl;
						clockHand++;
					}
					else {
						// 참조 비트가 0이면 교체 대상으로 선정
						int evictedKey = clockHand->key;
						cout << "  Cache is full. Evicting key " << evictedKey << endl;

						cacheMap.erase(evictedKey);
						clockHand = cacheList.erase(clockHand);
						break;
					}
				}
			}

			cacheList.push_back(Node(key));
			cacheMap[key] = prev(cacheList.end());

			// 캐시가 비어있었을 경우 포인터 초기화
			if (cacheList.size() == 1) {
				clockHand = cacheList.begin();
			}
		}

		cout << "Current Cache: [ ";
		for (const auto& node : cacheList) {
			cout << node.key << "(" << (node.refBit ? "1" : "0") << ") ";
		}
		cout << "]" << endl;
		cout << "-----------------------------------------" << endl;
	}
};

int main() {
	ClockCache cache(3);

	cache.put(1);
	cache.put(2);
	cache.put(3);
	cache.put(1);
	cache.put(4);
	cache.put(2);
	cache.put(5);

	return 0;
}
