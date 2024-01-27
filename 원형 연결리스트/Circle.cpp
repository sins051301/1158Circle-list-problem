#pragma warning(disable: 4996)
#include <iostream> //  전처리 지시자
#include<string>
#include <cassert>
//더미 연결리스트 구현

//template <typename T>
struct Node {
	struct Node* next;
	int data;
};

class Struct {
private:
	struct List {
		/*Node* head;*/ //head가 필요가 없음 tail->next가 가르키는 것은 head
		Node* tail;
		Node* cur;
		Node* back; // 삭제를 위한 용도
		int count;
	};
	List* list;
public:
	Struct() {
		list = ListInit(); //생성자로 초기화           아래부터 코드를 보면 암묵적으로 this생략가능
	}

	List* ListInit() {
		List* newlist = new List;
		//newlist->head = nullptr;
		newlist->count = 0;
		newlist->tail = nullptr;
		newlist->cur = nullptr;
		newlist->back = nullptr;
		return newlist;
	}
	bool LisEmpty() {
		if (this->list->tail == nullptr) {
			return true;
		}
		else
			return false;
	}
	int LFirst(int* data) { //첫 번째 데이터가 data가 가르키는 메모리에 저장된다.  
		if (this->list->tail == nullptr) {
			return 0;
		}
		this->list->cur = this->list->tail->next;
		this->list->back = this->list->tail;
		//if (this->list->head == nullptr) {
		//	return 0;                 //현재노드가 null이면 false반환
		//}
		*data = this->list->cur->data;
		return 1;

	}
	void LPushFront(int data) {
		Node* newNode = new Node;
		newNode->data = data;
		if (this->list->tail == nullptr) {
			this->list->tail = newNode;
			newNode->next = newNode;
			(this->list->count)++;
		}
		else {
			
			newNode->next = this->list->tail->next;
			this->list->tail->next = newNode;
			(this->list->count)++;
		}

	}
	void LPushBack(int data) {

		Node* newNode = new Node;
		newNode->data = data;
		if (this->list->tail == nullptr) {
			this->list->tail = newNode;
			newNode->next = newNode; 
			(this->list->count)++;
		}
		else {
			newNode->next = this->list->tail->next;
			this->list->tail->next = newNode;
			this->list->tail = newNode;  // 뒤로 추가와의 유일한 차이점임 (사실상 기능은 같음 원형연결이라서)
			(this->list->count)++;

		}

	}
	int LNext(int* data) {  //다음 노드로 이동 
	
		if (this->list->tail == nullptr) { //어짜피 원형 순회이기 때문에 tail이 null이 경우를 예외 처리함
			return 0;
		}
		this->list->back = this->list->cur;  // back을 먼저해야함
		this->list->cur = this->list->cur->next;
		*data = this->list->cur->data;
		return 1;
	}
	//현재 참조값을 삭제한 후 삭제 값 반환 
	int LRemove() {  //LFirst LNext 함수의 마지막 반환 데이터를 삭제
	//두가지 예외 처리 필요! 
		Node* del = this->list->cur;  //현재 참조값을 기준으로 삭제
		int delData = del->data;
		if (this->list->tail == del) {  //삭제할 노드가 꼬리일 떄
	
			if (this->list->tail == this->list->back) { //노드가 하나 남았을 떄
				this->list->tail = nullptr;
			}
			else {
				this->list->tail = this->list->back;  //꼬리와 뒤가 가르키는게 같아짐
			}

		}
		this->list->back->next = this->list->cur->next;
		this->list->cur = this->list->back;
		delete del;
		(this->list->count)--;
		return delData;
	}
	int LCount() {  //있는 노드 개수 반환
		return this->list->count;
	}
	~Struct() {
		delete this->list->tail;
		delete this->list;     //클래스의 소멸시 자동 동적할당 해제
	}

	void LClear() {
		int *data = new int;
		
		if (this->list != nullptr) {

			while (this->LFirst(data)) {
				this->LRemove();
				
			}
		}
	}

};

int main() {
	using namespace std;
	Struct list;

	int* data = new int;
	int N, K, i;
	scanf("%d %d", &N, &K);
	for ( i = 1; i <= N; i++) {
		list.LPushBack(i);
	}
	list.LClear();

	i = 1;
	list.LFirst(data);
	cout << "<";
	while (!list.LisEmpty()) {
		if (i % K ==0 && list.LCount() >= 2) {
			cout << list.LRemove()<<", ";
		}
		else if (i % K == 0 && list.LCount() < 2) {
			cout << list.LRemove() << ">";
		}
		i++;
		list.LNext(data);
	}
	

	



}