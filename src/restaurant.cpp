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

const int maxTable=9;
Table tables[maxTable];   // 테이블 관리하기 위한 객체 배열
int tableCount=0;   // 테이블 개수 세는 변수

// 테이블 추가 함수
void addTable(int n,bool o,int p){
    if(tableCount<maxTable)
        tables[tableCount++]=Table(n,o,p);
    else
        cout<<"빈 테이블이 없습니다."<<endl;
}

// 테이블 퇴점 처리하는 함수
void outTable(int n){
    tables[n-1].occupy=false;   // 퇴점 테이블의 점유 여부를 false로 바꿈
}
// 퇴점 된 테이블 중 우선순위 알려주는 함수
void cleanTable(){
    Table cleanTables[maxTable];    // 퇴점한 테이블 관리하기 위한 객체 배열
    int cleanCount=0;   // 퇴점 테이블 개수 세는 변수

    // 퇴점한 테이블 찾기
    for(int i=0;i<tableCount;i++){
        if(!tables[i].occupy)
            cleanTables[cleanCount++]=tables[i];
    }

    if(cleanCount==0){
        cout<<"청소할 테이블이 없습니다."<<endl;
        return;
    }
    
    // 퇴점한 테이블 선호도 우선순위 알려주는 함수
}

int main(){
    // 테이블 입점
    addTable(1,true,10);   // 1번 테이블, 선호도 10
    addTable(2,true,7);    // 2번 테이블, 선호도 7
    addTable(3,true,6);    // 3번 테이블, 선호도 6
    addTable(4,true,9);    // 4번 테이블, 선호도 9
    addTable(5,true,4);    // 5번 테이블, 선호도 4
    addTable(6,true,5);    // 6번 테이블, 선호도 5
    addTable(7,true,8);    // 7번 테이블, 선호도 8
    addTable(8,true,2);    // 8번 테이블, 선호도 2
    addTable(9,true,3);    // 9번 테이블, 선호도 3

    // 테이블 퇴점 처리
    outTable(4);
    outTable(5);
    outTable(9);

    // 퇴점한 테이블 중 선호도에 따라 정렬하고 알려줌
}