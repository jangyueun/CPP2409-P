#include <iostream>
using namespace std;

const int numRows=3;    // 행 개수
const int numCols=3;    // 열 개수

class Table{    // 테이블 클래스
public:
    int tableNumber; // 테이블 번호
    int preference; // 손님 선호도(높을수록 우선순위 높음)
    bool occupy;    // 테이블 점유 여부
    bool clean; // 테이블 청소 여부
    
    Table(){    // 기본 생성자
        tableNumber=0;
        preference=0;
        occupy=false;
        clean=false;
    }
    Table(int n,int p){
        tableNumber=n;
        preference=p;
        occupy=false;
        clean=true;
    }

    //테이블 상태 반환(O,X,_)
    char getStatus() const{
        if(occupy) return 'O';  // 점유된 테이블
        else if (clean) return '_'; // 청소된 테이블
        else return 'X';    // 퇴점한 테이블
    } 
};

// 테이블 초기화
void initialTables(Table tables[numRows][numCols]){
    int tableNumber=1;  // 테이블 번호 시작
    int preference=9;   // 선호도 시작
    for (int i=0;i<numRows;++i)
        for(int j=0;j<numCols;++j)
            tables[i][j]=Table(tableNumber++,preference--);
}

// 테이블 상태 출력(3X3 배열)
void printTables(Table tables[numRows][numCols]){
    for(int i=0;i<numRows;i++){
        cout<<"---|---|----"<<endl; // 구분선
        for(int j=0;j<numCols;j++){
            cout<<tables[i][j].getStatus(); // Table 객체 상태 출력
            if(j==numCols-1)    // 마지막 열 아니면 구분자 출력
                cout<<"  |";
        }
        cout<<endl;
    }
    cout<<"---|---|----"<<endl; //마지막 구분선
}

// 번호를 행과 열로 변환
void change(int tableNumber,int &row, int &col){
    row = (tableNumber - 1) / numCols;
    col = (tableNumber - 1) % numCols;
}

// 테이블 입점
void entryTable(Table tables[numRows][numCols],int tableNumber){
    int row, col;
    change(tableNumber, row, col);

    if(row<0||row>=numRows||col<0||col>=numCols){
        cout<<"잘못된 테이블 번호입니다."<<endl;
        return;
    }
    
    
}

// 테이블 퇴점
void leaveTable(Table tables[numRows][numCols], int tableNumber){
    int row, col;
    change(tableNumber, row, col);

    if(row<0||row>=numRows||col<0||col>=numCols){
        cout<<"잘못된 테이블 번호입니다."<<endl;
        return;
    }
    
    
}

//청소 우선순위


int main(){
    Table tables[numRows][numCols]; // 테이블 입력할 객체 배열
    initialTables(tables);  // 테이블 초기화

    while(true){
        printTables(tables);    // 현재 테이블 상태 출력

        int choice;
        cout<<endl;
        cout<<"1. 입점 테이블 입력"<<endl;
        cout<<"2. 퇴점 테이블 입력"<<endl;
        cout<<"3. 청소한 테이블 입력"<<endl;
        cout<<"4. 테이블 청소 우선순위"<<endl;
        cout<<"0. 프로그램 종료"<<endl;
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
            cout<<"청소한 테이블 번호를 입력하세요:";
            cin>>tableNumber;
            //cleanTable(tables,tableNumber);
        case 4:
            //cleanTable(tables);//청소우선순위 함수
            break;
        case 0:
            cout<<"프로그램을 종료합니다"<<endl;
            return 0;
        default:
            cout<<"잘못된 입력입니다."<<endl;
            break;
        }
    }
    return 0;
}