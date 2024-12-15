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
        cout<<"---|---|---"<<endl; // 구분선
        for(int j=0;j<numCols;j++){
            cout<<tables[i][j].getStatus(); // Table 객체 상태 출력
            if(j==numCols-1)
                break;
            cout<<"  |";
        }
        cout<<endl;
    }
    cout<<"---|---|---"<<endl; //마지막 구분선
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

    if(tables[row][col].occupy)
        cout<<"테이블"<<tableNumber<<"은 이미 입점 중입니다. 다른 테이블을 선택하세요."<<endl;
    else if(!tables[row][col].clean){
        cout<<"테이블"<<tableNumber<<"은 청소되지 않았습니다. 먼저 청소를 완료하세요."<<endl;
    }
    else{
        tables[row][col].occupy=true;
        tables[row][col].clean=false;   // 입점 시 청소 상태 해제
        cout<<"테이블"<<tableNumber<<" 입점했습니다."<<endl;
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
    
    if(!tables[row][col].occupy)
        cout<<"테이블"<<tableNumber<<"은 이미 퇴점했습니다."<<endl;
    else{
        tables[row][col].occupy=false;
        cout<<"테이블"<<tableNumber<<" 퇴점했습니다."<<endl;
    }
}

// 테이블 청소
void cleanTable(Table tables[numRows][numCols], int tableNumber){
    int row, col;
    change(tableNumber, row, col);

    if(row<0||row>=numRows||col<0||col>=numCols){
        cout<<"잘못된 테이블 번호입니다."<<endl;
        return;
    }

    if(tables[row][col].occupy)
        cout<<"테이블"<<tableNumber<<"은 손님이 입점해 있는 테이블 입니다."<<endl;
    else if(tables[row][col].clean)
        cout<<"테이블"<<tableNumber<<"은 이미 청소한 테이블 입니다."<<endl;
    else{
        tables[row][col].clean=true;
        cout<<"테이블"<<tableNumber<<" 청소했습니다."<<endl;
    }
}

//청소 우선순위(선호도 높은 순으로 출력)
void priorityTable(Table tables[numRows][numCols]){
    // 청소해야 할 테이블 임시 저장할 배열
    Table tempTables[numRows*numCols];
    int count=0;

    //퇴점하고 청소되지 않은 테이블만 배열에 추가
    for(int i=0;i<numRows;i++){
        for(int j=0;j<numCols;j++){
            if(!tables[i][j].occupy&&!tables[i][j].clean)
                tempTables[count++]=tables[i][j];
        }
    }

    if(count==0)
        cout<<"청소할 테이블이 없습니다."<<endl;
    else{
        // 선호도에 따라 정렬 (버블 정렬 사용)
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (tempTables[j].preference < tempTables[j + 1].preference) {
                    Table temp = tempTables[j];
                    tempTables[j] = tempTables[j + 1];
                    tempTables[j + 1] = temp;
                }
            }
        }

        cout<<"청소 우선순위 : ";
        for(int i=0;i<count;++i){
            cout<<"테이블"<<tempTables[i].tableNumber<<" (선호도"<<tempTables[i].preference<<")";
            if(i<count-1)
                cout<<"->";
        }
        cout<<endl;
    }
}

int main(){
    Table tables[numRows][numCols]; // 테이블 입력할 객체 배열
    initialTables(tables);  // 테이블 초기화

    while(true){
        printTables(tables);    // 현재 테이블 상태 출력

        int choice;
        cout<<endl;
        cout<<"0. 프로그램 종료"<<endl;
        cout<<"1. 입점 테이블 입력"<<endl;
        cout<<"2. 퇴점 테이블 입력"<<endl;
        cout<<"3. 청소한 테이블 입력"<<endl;
        cout<<"4. 테이블 청소 우선순위"<<endl;
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
            cleanTable(tables,tableNumber); // 청소 처리 함수
            break;
        case 4:
            priorityTable(tables); // 청소우선순위 함수
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