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

// 테이블 입점
void entryTable(Table tables[],int tableNumber){
    if(tableNumber<1||tableNumber>MAXTABLE){
        cout<<"잘못된 테이블 번호입니다."<<endl;
        return;
    }
    
    if(!tables[tableNumber-1].occupy){
        tables[tableNumber-1].occupy=true;
        cout<<tableNumber<<"번 테이블 입점했습니다."<<endl;
    }
    else
        cout<<"이미 입점한 테이블입니다."<<endl;
}

// 테이블 퇴점
void leaveTable(Table tables[],int tableNumber){
    if(tableNumber<1||tableNumber>MAXTABLE){
        cout<<"잘못된 테이블 번호입니다."<<endl;
        return;
    }
    
    if(tables[tableNumber-1].occupy){
        tables[tableNumber-1].occupy=false;
        cout<<tableNumber<<"번 테이블 퇴점했습니다."<<endl;
    }
    else
        cout<<"이미 퇴점한 테이블입니다."<<endl;
}

//청소 우선순위
void cleanTable(Table tables[]){
    Table cleanTable[MAXTABLE];
    int cleanCount=0;

    for(int i=0;i<MAXTABLE;i++){    // 퇴점한 테이블만 배열에 입력
        if(!tables[i].occupy)
            cleanTable[cleanCount++]=tables[i];
    }


}

int main(){
    Table tables[MAXTABLE]; // 테이블 입력할 객체 배열
    initialTables(tables);  // 테이블 초기화

    while(true){
        int choice;
        cout<<endl;
        cout<<"1. 입점 테이블 입력"<<endl;
        cout<<"2. 퇴점 테이블 입력"<<endl;
        cout<<"3. 테이블 청소 우선순위"<<endl;
        cout<<"4. 프로그램 종료"<<endl;
        cout<<"원하는 번호를 입력하세요:";
        cin>>choice;
 
        int tableNumber;    // 입력한 테이블 번호 저장할 변수
        switch(choice){
        case 1:
            cout<<"입점 테이블 번호를 입력하세요:";
            cin>>tableNumber;
            entryTable(tables,tableNumber); // 입점 처리 함수
            break;
        case 2:
            cout<<"퇴점 테이블 번호를 입력하세요:";
            cin>>tableNumber;
            leaveTable(tables,tableNumber);//퇴점 처리 함수
            break;
        case 3:
            cleanTable(tables);//청소우선순위 함수
            break;
        case 4:
            cout<<"프로그램을 종료합니다"<<endl;
            return 0;
        default:
            cout<<"잘못된 입력입니다."<<endl;
            break;
        }
    }
    return 0;
}