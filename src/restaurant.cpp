#include <iostream>
using namespace std;

class Table{
public:
    int number; // 테이블 번호
    bool occupy;    // 테이블 점유 여부
    int preference; // 손님 선호도(높을수록 우선순위 높음)

    Table(){    // 기본 생성자
        number=0;
        occupy=false;
        preference=0;
    }
    Table(int n,bool o,int p){
        number=n;
        occupy=o;
        preference=p;
    }
};

Table tables[10];   // 테이블 관리하기 위한 객체 배열
int tableCount=0;   // 테이블 개수 세는 변수

// 테이블 추가 함수
void addTable(int n,bool o,int p){
    if(tableCount<10)
        tables[tableCount++]=Table(n,o,p);
    else
        cout<<"빈 테이블이 없습니다."<<endl;
}

// 테이블 퇴점 처리하는 함수
// 퇴점 된 테이블 중 우선순위 알려주는 함수

int main(){
    // 테이블 입점
    // 테이블 퇴점 처리
    // 퇴점한 테이블 중 선호도에 따라 정렬하고 알려줌
}