#include <iostream>
#include <vector>
using namespace std;

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

    // operator<< 오버로딩
    friend ostream& operator<<(ostream& os, const Table& table) {
        os << table.getStatus();
        return os;
    }
};

// 테이블 초기화
void initializeTables(vector<vector<Table>>& tables, int rows, int cols){
     int tableNumber = 1;
    int preference = rows * cols; // 선호도는 테이블 번호 반대로 설정
    for (int i = 0; i < rows; ++i) {
        vector<Table> row;
        for (int j = 0; j < cols; ++j) {
            row.emplace_back(tableNumber++, preference--);
        }
        tables.push_back(row);
    }
}

// 테이블 상태 출력
void printTables(vector<vector<Table>>& tables) {
    int numRows = tables.size();        // 행 개수
    int numCols = tables[0].size();     // 열 개수

    for (int i = 0; i < numRows; ++i) {
        // 구분선 출력
        for (int j = 0; j < numCols; ++j) {
            cout << "---";
            if (j < numCols - 1) cout << "|"; // 열 사이에만 구분선 출력
        }
        cout << endl;

        // 테이블 상태 출력
        for (int j = 0; j < numCols; ++j) {
            cout << " " << tables[i][j].getStatus() << " ";
            if (j < numCols - 1) cout << "|"; // 열 사이에만 구분선 출력
        }
        cout << endl;
    }

    // 마지막 구분선 출력
    for (int j = 0; j < numCols; ++j) {
        cout << "---";
        if (j < numCols - 1) cout << "|";
    }
    cout << endl;
}

// 테이블 번호를 좌표로 변환
bool changeToCoordinates(int tableNumber, int rows, int cols, int& row, int& col) {
    if (tableNumber < 1 || tableNumber > rows * cols) return false;
    row = (tableNumber - 1) / cols;
    col = (tableNumber - 1) % cols;
    return true;
}

// 테이블 입점
void entryTable(vector<vector<Table>>& tables, int tableNumber, int rows, int cols) {
    try {
        int row, col;
        if (!changeToCoordinates(tableNumber, rows, cols, row, col)) {
            throw invalid_argument("잘못된 테이블 번호입니다.");
        }

        Table& table = tables[row][col];
        if (table.occupy) {
            throw logic_error("테이블이 이미 점유 중입니다.");
        } else if (!table.clean) {
            throw runtime_error("테이블이 청소되지 않았습니다.");
        }

        table.occupy = true;
        table.clean = false;
        cout << "테이블 " << tableNumber << " 입점했습니다." << endl;

    } catch (const invalid_argument& e) {
        cout<< e.what() << endl;
    } catch (const logic_error& e) {
        cout<< e.what() << endl;
    } catch (const runtime_error& e) {
        cout <<e.what() << endl;
    }
}

// 테이블 퇴점
void leaveTable(vector<vector<Table>>& tables, int tableNumber, int rows, int cols) {
    try {
        int row, col;
        if (!changeToCoordinates(tableNumber, rows, cols, row, col)) {
            throw invalid_argument("잘못된 테이블 번호입니다.");
        }

        Table& table = tables[row][col];
        if (!table.occupy) {
            throw logic_error("테이블이 이미 퇴점되었습니다.");
        }

        table.occupy = false;
        cout << "테이블 " << tableNumber << " 퇴점했습니다." << endl;

    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    } catch (const logic_error& e) {
        cout << e.what() << endl;
    }
}

// 테이블 청소
void cleanTable(vector<vector<Table>>& tables, int tableNumber, int rows, int cols) {
    try {
        int row, col;
        if (!changeToCoordinates(tableNumber, rows, cols, row, col)) {
            throw invalid_argument("잘못된 테이블 번호입니다.");
        }

        Table& table = tables[row][col];
        if (table.occupy) {
            throw logic_error("테이블이 점유 중입니다. 퇴점 후 청소할 수 있습니다.");
        } else if (table.clean) {
            throw runtime_error("테이블이 이미 청소되었습니다.");
        }

        table.clean = true;
        cout << "테이블 " << tableNumber << " 청소했습니다." << endl;

    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    } catch (const logic_error& e) {
        cout << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

// 청소 우선순위 정렬 (버블 정렬 사용)
void sortByPreference(vector<Table>& toClean) {
    for (size_t i = 0; i < toClean.size() - 1; ++i) {
        for (size_t j = 0; j < toClean.size() - i - 1; ++j) {
            if (toClean[j].preference < toClean[j + 1].preference) {
                Table temp = toClean[j];
                toClean[j] = toClean[j + 1];
                toClean[j + 1] = temp;
            }
        }
    }
}

// 청소 우선순위
void priorityTable(const vector<vector<Table>>& tables) {
    try {
        vector<Table> toClean;

        // 청소가 필요한 테이블 모으기
        for (const auto& row : tables) {
            for (const auto& table : row) {
                if (!table.occupy && !table.clean) {
                    toClean.push_back(table);
                }
            }
        }

        if (toClean.empty()) {
            throw runtime_error("청소할 테이블이 없습니다.");
        }

        // 선호도 기준 내림차순 정렬 (버블 정렬)
        sortByPreference(toClean);

        cout << "청소 우선순위: ";
        for (size_t i = 0; i < toClean.size(); ++i) {
            cout << "테이블 " << toClean[i].tableNumber << " (선호도 " << toClean[i].preference << ")";
            if (i < toClean.size() - 1) cout << " -> ";
        }
        cout << endl;

    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

int main(){
    int rows, cols;
    cout << "테이블 행 개수를 입력하세요: ";
    cin >> rows;
    cout << "테이블 열 개수를 입력하세요: ";
    cin >> cols;

    vector<vector<Table>> tables;
    initializeTables(tables, rows, cols);

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
            entryTable(tables,tableNumber, rows, cols); // 입점 처리 함수
            break;
        case 2:
            cout<<"퇴점 테이블 번호를 입력하세요:";
            cin>>tableNumber;
            leaveTable(tables,tableNumber, rows, cols);//퇴점 처리 함수
            break;
        case 3:
            cout<<"청소한 테이블 번호를 입력하세요:";
            cin>>tableNumber;
            cleanTable(tables,tableNumber, rows, cols); // 청소 처리 함수
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