#include <iostream>
using namespace std;
#define MAXTABLE 9

class Table{    // 테이블 클래스
public:
    int number; // 테이블 번호
    int preference; // 손님 선호도(높을수록 우선순위 높음)
    bool occupy;    // 테이블 점유 여부
    
    Table(){    // 기본 생성자
        number=0;
        preference=0;
        occupy=false;
    }
    Table(int n,int p){
        number=n;
        preference=p;
        occupy=false;
    }
};

// 테이블 초기화
void initialTables(Table tables[]){
    for(int i=0;i<MAXTABLE;i++)
        tables[i]=Table(i+1,10-i);  // 테이블 번호 1~9, 선호도 10에서 감소
} 


int main(){
    Table tables[MAXTABLE];
    initialTables(tables);

    while(true){
        int choice;
        cout<<"1. 입점 테이블 입력"<<endl;
        cout<<"2. 퇴점 테이블 입력"<<endl;
        cout<<"3. 테이블 청소 순위"<<endl;
        cout<<"원하는 번호를 입력하세요:";
        cin>>choice;

        int number;
        switch(choice){
        case 1:
            cout<<"입점 테이블 번호를 입력하세요:";
            cin>>number;
            //입점 처리 함수
            break;
        case 2:
            cout<<"퇴점 테이블 번호를 입력하세요:";
            cin>>number;
            //퇴점 처리 함수
            break;
        case 3:
            //청소우선순위 함수
            break;
        default:
            cout<<"잘못된 입력입니다."<<endl;
        }
    }
    return 0;
}
    