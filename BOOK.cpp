#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <map>
using namespace std;

struct BOOK {
    int ID;
    string Title;
    string Author;
    int Year;
    float Cost;
    int Quantity;
};

struct NODE {
    BOOK Key;
    NODE* pNext;
};

NODE* CreateNode(BOOK Data);
void AddBook(NODE* &pHead, BOOK Data);
void PrintList(NODE* pHead);
void InputBook(BOOK& Data);
void PrintBook(BOOK Data);
void PrintBookList(NODE* pHead);
int CountBook(NODE *pHead);
NODE* ReverseList(NODE* pHead);
void DeleteBook(NODE* &pHead, const int& year);
float GetTotal(const BOOK& book);
float GetTotalPrice(NODE* pHead);
void ClearAllBook(NODE* &pHead);
string GetFavoriteAuthor(NODE* pHead);
void AddBeforeKthBook(NODE* &pHead, int k, BOOK Data);
void DeleteBeforeKthBook(NODE* &pHead, int k);

NODE* CreateNode(BOOK Data) {
    NODE* pNode = new NODE;
    pNode->Key = Data;
    pNode->pNext = NULL;
    return pNode;
}

void AddBook(NODE* &pHead, BOOK Data) {
    NODE* pNode = pHead;
    while (pNode != NULL) {
        if (pNode->Key.ID == Data.ID) {
            cout << "ID da ton tai. Vui long nhap mot cai khac." << endl;
            return;
        }
        pNode = pNode->pNext;
    }

    NODE* newNode = CreateNode(Data);
    if (pHead == NULL) {
        pHead = newNode;
    } else {
        pNode = pHead;
        while (pNode->pNext != NULL) {
            pNode = pNode->pNext;
        }
        pNode->pNext = newNode;
    }
}

void PrintList(NODE* pHead) {
    NODE* pNode = pHead;
    while (pNode != NULL) {
        PrintBook(pNode->Key);
        pNode = pNode->pNext;
    }
    cout << endl;
}

void InputBook(BOOK& Data) {
    cout << "\nID: ";
    while (!(cin >> Data.ID)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vui long nhap so nguyen." << endl;
        cout << "ID: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Title: ";
    getline(cin, Data.Title);

    cout << "Author: ";
    getline(cin, Data.Author);

    cout << "Year: ";
    while (!(cin >> Data.Year)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vui long nhap so nguyen." << endl;
        cout << "Year: ";
    }

    cout << "Cost: ";
    while (!(cin >> Data.Cost)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vui long nhap so." << endl;
        cout << "Cost: ";
    }

    cout << "Quantity: ";
    while (!(cin >> Data.Quantity)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vui long nhap so nguyen." << endl;
        cout << "Quantity: ";
    }
}

void PrintBook(BOOK Data) {
    cout << "ID: " << Data.ID << endl;
    cout << "Title: " << Data.Title << endl;
    cout << "Author: " << Data.Author << endl;
    cout << "Year: " << Data.Year << endl;
    cout << "Cost: " << Data.Cost << endl;
    cout << "Quantity: " << Data.Quantity << endl;
}

void PrintBookList(NODE* pHead){
    int count = 0;
    NODE* pNode = pHead;
    
    while (pNode != NULL) {
        cout << "\nBook " << ++count << ":" << endl;
        PrintBook(pNode->Key);
        pNode = pNode->pNext;
    }
}

int CountBook(NODE *pHead){
    int count=0;
    NODE* pNode = pHead;
    while (pNode != NULL) {
        count++;
        pNode = pNode->pNext;
    }
    return count;
}

void DeleteBook(NODE* &pHead, const int & year){
    if (pHead == NULL) {
        cout << "\nKhong co sach trong danh sach." << endl;
        return;
    }

    NODE* pNode = pHead;
    NODE* pPrev = NULL;

    while (pNode != NULL) {
        if (pNode->Key.Year == year) {
            if (pPrev == NULL) {
                // If pNode is the head node
                pHead = pNode->pNext;
            } else {
                pPrev->pNext = pNode->pNext;
            }
            delete pNode;
            cout << "\nDa xoa sach xuat ban nam " << year << " trong danh sach." << endl;
            return;
        }
        pPrev = pNode;
        pNode = pNode->pNext;
    }
    cout << "\nKhong co sach xuat ban nam " << year << " trong danh sach."<< endl;
}

void FindBooks(NODE* pHead, const string& author) {
    NODE* pNode = pHead;
    bool found = false;

    while (pNode != NULL) {
        if (pNode->Key.Author == author) {
            cout << "\nThong tin sach co " << author << ":" << endl;
            PrintBook(pNode->Key);
            found = true;
            break;
        }
        pNode = pNode->pNext;
    }

    if (!found) {
        cout << "\nKhong tim thay sach co ten tac gia la " << author << " trong danh sach." << endl;
    }
}

NODE* ReverseList(NODE* pHead) {
    NODE* pReversedHead = NULL;
    NODE* pNode = pHead;
    
    while (pNode != NULL) {
        NODE* pNext = pNode->pNext;
        pNode->pNext = pReversedHead;
        pReversedHead = pNode;
        pNode = pNext;
    }
    
    return pReversedHead;
}

float GetTotal(const BOOK& book) {
    return book.Quantity * book.Cost;
}

float GetTotalPrice(NODE* pHead) {
    float total = 0.0;
    NODE* pNode = pHead;
    
    while (pNode != NULL) {
        total += GetTotal(pNode->Key);
        pNode = pNode->pNext;
    }
    
    return total;
}

void ClearAllBook(NODE* &pHead) {
    while (pHead != NULL) {
        NODE* temp = pHead;
        pHead = pHead->pNext;
        delete temp;
    }
    cout << "\nDanh sach da duoc lam rong." << endl;
}

string GetFavoriteAuthor(NODE* pHead) {
    if (pHead == NULL) {
        return "Khong co sach trong danh sach";
    }

    map<string, int> authorCount; // Sử dụng một map để lưu trữ số lượng sách của mỗi tác giả

    // Lặp qua danh sách sách và đếm số lượng sách của mỗi tác giả
    NODE* pNode = pHead;
    while (pNode != NULL) {
        string author = pNode->Key.Author;
        authorCount[author]++;
        pNode = pNode->pNext;
    }

    // Tìm tác giả có số lượng sách nhiều nhất
    string favoriteAuthor;
    int maxCount = 0;
    for (auto it = authorCount.begin(); it != authorCount.end(); ++it) {
        if (it->second > maxCount) {
            maxCount = it->second;
            favoriteAuthor = it->first;
        }
    }

    return favoriteAuthor;
}

void AddBeforeKthBook(NODE* &pHead, int k, BOOK Data) {
    if (pHead == NULL) {
        cout << "\nDanh sach rong. Them vao dau danh sach.\n";
        AddBook(pHead, Data);
        return;
    }

    if (k == 0) {
        NODE* newNode = CreateNode(Data);
        newNode->pNext = pHead;
        pHead = newNode;
        return;
    }

    int count = 0;
    NODE* pNode = pHead;
    NODE* pPrev = NULL;

    while (pNode != NULL && count < k) {
        pPrev = pNode;
        pNode = pNode->pNext;
        count++;
    }

    if (pNode == NULL) {
        AddBook(pHead, Data);
        return;
    } else {
        cout << "\nThem vao truoc dau sach thu " << k << " trong danh sach." << endl;
        NODE* newNode = CreateNode(Data);
        newNode->pNext = pNode;
        if (pPrev != NULL) {
            pPrev->pNext = newNode;
        } else {
            pHead = newNode;
        }
    }
}

void DeleteBeforeKthBook(NODE* &pHead, int k) {
    if (pHead == NULL) {
        cout << "\nDanh sach rong." << endl;
        return;
    }
    else if (k == 1) {
        // Xóa đầu sách ở đầu danh sách
        NODE* temp = pHead;
        pHead = pHead->pNext;
        delete temp;
        cout << "\nDa xoa dau sach o dau danh sach." << endl;
        return;
    }
    int count = 1;
    NODE* pNode = pHead;
    NODE* pPrev = NULL;
    // Di chuyển đến nút trước nút thứ k
    while (pNode->pNext != NULL && count < k) {
        pPrev = pNode;
        pNode = pNode->pNext;
        count++;
    }
    // Kiểm tra nếu nút hiện tại là null hoặc k = N
    if (pNode == NULL || pNode->pNext == NULL) {
        if (count == k) {
            // Nếu k = N, xóa nút cuối cùng
            delete pNode;
            if (pPrev != NULL) {
                pPrev->pNext = NULL;
            } else {
                pHead = NULL;
            }
            cout << "\nDa xoa dau sach cuoi cung trong danh sach." << endl;
            return;
        } else {
            // Nếu nút hiện tại là null, không thể xóa nút trước nút thứ k
            cout << "\nKhong the xoa dau sach truoc dau sach thu " << k << " vi khong co dau sach sau no." << endl;
            return;
        }
    }
    // Xóa nút
    NODE* temp = pPrev->pNext;
    pPrev->pNext = pNode->pNext;
    delete temp;
    cout << "\nDa xoa dau sach truoc dau sach thu " << k << " trong danh sach." << endl;
}



int main(){
    NODE* pHead = NULL;
    BOOK Data;
    int choice;
    do {
        cout << "\n1. Them sach" << endl;
        cout << "2. In ra danh sach" << endl;
        cout << "3. Tim sach" << endl;
        cout << "4. Dao nguoc danh sach" << endl;
        cout << "5. Xoa sach theo nam" << endl;
        cout << "6. Tinh tong tien sach" << endl;
        cout << "7. Tim tac gia viet nhieu sach nhat" << endl;
        cout << "8. Them sach vao dau sach thu k" << endl;
        cout << "9. Xoa dau sach truoc dau sach thu k" << endl;
        cout << "10. Xoa toan bo danh sach" << endl;
        cout << "11. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                InputBook(Data);
                AddBook(pHead, Data);
                break;
            case 2:
                PrintBookList(pHead);
                cout<<"\nTong so dau sach: "<<CountBook(pHead)<<endl;
                break;
            case 3:
                {
                    string author;
                    cout << "\nNhap ten sach can tim: ";
                    cin.ignore();
                    getline(cin, author);
                    FindBooks(pHead, author);
                    break;
                }
            case 4:
                pHead = ReverseList(pHead);
                cout << "\nDanh sach da duoc dao nguoc." << endl;
                break;
            case 5:
                {
                    int year;
                    cout << "\nNhap nam xuat ban: ";
                    cin >> year;
                    DeleteBook(pHead, year);
                    PrintBookList(pHead);
                    break;
                }
            case 6:
                cout << "\nTong tien cua tat ca cac sach: " << fixed << setprecision(2) << GetTotalPrice(pHead) << endl;
                break;
            case 7:
                cout << "\nTac gia viet nhieu sach nhat: " << GetFavoriteAuthor(pHead) << endl;
                break;
            case 8:
            {
                int k;
                cout << "\nNhap dau sach thu k: ";
                cin >> k;
                InputBook(Data);
                AddBeforeKthBook(pHead, k, Data);
                PrintBookList(pHead);
                break;
            }
            case 9:
            {
                int N = CountBook(pHead); // Đếm số đầu sách trong danh sách
                int k;
                cout << "\nNhap dau sach thu k: ";
                cin >> k;
                DeleteBeforeKthBook(pHead, k);
                PrintBookList(pHead);
                break;
            }
            case 10:
                ClearAllBook(pHead);
                break;
            case 11:
                break;
            default:
                cout << "\nLua chon sai. Vui long nhap lai." << endl;
        }
    } while (choice != 11);

    return 0;
}
