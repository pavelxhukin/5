#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

template <typename Type>
void star(Type sign) {
    for (int i = 0; i < 100;i++) {
        cout << sign;
    }cout << endl;
}

class Worker {
private:


public:
    string addres;
    string god_rojd;
    string god_rabot;
    string name;
    string name2;
    string name3;
    string pos;
    Worker() {
        god_rojd = god_rabot = name3 = name = name2 = addres = "";
    }
    Worker(string add,string grj, string grb, string n1, string n2, string n3,string pos) {
        this->god_rojd = grj;
        this->god_rabot = grb;
        this->addres = add;
        this->pos = pos;
        this->name = n1;
        this->name2 = n2;
        this->name3 = n3;
    }
    string getAddres() {
        return addres;
    }
    string ToString();
    void InitMyEntity();
};
string Worker::ToString() {
    string st = "";
    st = this->addres + "\t|\t" + this->god_rojd + "\t|\t" + this->god_rabot + "\t|\t" +
        this->name + "\t|\t" + this->name2 + "\t|\t" + this->name3 + "\t|\t" + this->pos;
    return st;
}
void Worker::InitMyEntity() {
    cout << "Enter addres: ";
    getline(cin, addres);
    getline(cin, addres);
    cout << "Enter god rojdenia: ";
    getline(cin, god_rojd);
    cout << "Enter god rabot: ";
    getline(cin, god_rabot);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter 2 Name: ";
    getline(cin, name2);
    cout << "Enter 3 Name: ";
    getline(cin, name3);
    cout << "Enter Pos: ";
    getline(cin, pos);
}

class WorkerList {
private:

    void Swap(Worker& l, Worker& m);

public:
    vector<Worker> workerList;
    Worker PrintFile();
    Worker PrintFile(int n);
    void AddElement(Worker data);
    void PrintAutolist();
    void InitList();
    void RemoveElement(int n);
    void findAddres();
    int len();
};
void WorkerList::AddElement(Worker data) {
    workerList.push_back(data);
}
void WorkerList::PrintAutolist() {
    int j = 0;
    vector<Worker>::iterator b = workerList.begin();
    vector<Worker>::iterator e = workerList.end();
    star("-");
    for (auto i = b; i != e; i++, j++) {
        cout << j << "\t|\t" << (*i).ToString() << endl;
    }
    star("-");
}
int WorkerList::len() {
    return workerList.size();
}
Worker WorkerList::PrintFile() {
    return workerList.at(workerList.size() - 1);
}
Worker WorkerList::PrintFile(int n) {
    return workerList.at(n);
}
void WorkerList::InitList() {
    Worker* temp = new Worker;
    temp->InitMyEntity();
    AddElement(*temp);
    delete temp;
}
void WorkerList::RemoveElement(int n) {
    auto b = workerList.begin();
    workerList.erase(b + n);
}
void WorkerList::findAddres() {
    string addresToFind;
    getline(cin, addresToFind);
    getline(cin, addresToFind);
    int length = workerList.size();
    for (int i = 0; i < length; i++) {
        if (workerList.at(i).getAddres() == addresToFind) {
            star("*");
            cout << workerList.at(i).ToString()<<endl;
        }

    }
    star("*");
}

ostream& operator<<(ostream& os, const Worker& data) {

    os <<data.addres << "|" << data.god_rojd << "|" << data.god_rabot << "|" << data.name << "|" << data.name2 << "|" << data.name3 << "|" << data.pos;
    return os;
}

int menu() {
    cout << "\n0. Выход" << endl;
    cout << "1. Загрузить" << endl;
    cout << "2. Добавить элемент" << endl;
    cout << "3. Отобразить" << endl;
    cout << "4. Удалить элемент" << endl;
    cout << "5. Поиск по адресу" << endl;
    cout << "6. Сохранение" << endl;
    int i;
    cout << endl;
    cin >> i;
    cout << endl;
    return i;
}
void read(string path, WorkerList& list) {
    fstream fs;
    fs.open(path, fstream::in | fstream::out);
    int position = 0;

    if (fs.is_open()) {
        while (!fs.eof())
        {
            string pars[7] = { "","","","","","","" };
            string S = "";
            position = 0;
            getline(fs, S);
            for (int i = 0; i < S.length(); i++) {
                if (S[i] == '|') {
                    ++position;
                    continue;
                }
                pars[position] += S[i];
            }
            Worker data(pars[0], pars[1], pars[2], pars[3], pars[4], pars[5], pars[6]);
            list.AddElement(data);
        }
    }
    fs.close();
}
void write(string path, WorkerList list) {
    ofstream fs;
    fs.open(path, fstream::out);
    Worker data;
    if (fs.is_open()) {
        cout << "Файл";
        for (int i = 0; i < list.len(); i++) {
            data = list.workerList.at(i);
            fs << data << endl;
        }
    }
    fs.close();
}

void writeAdd(string path, Worker list, string message) {
    ofstream fs;
    fs.open(path, fstream::app);
    Worker data;
    if (fs.is_open()) {

        fs << message << " : ";
        fs << list << endl;
    }
    fs.close();
}


int main()
{
    setlocale(LC_ALL, "ru");
    string path = "Save.txt";
    string path2 = "Result.txt";
    WorkerList list;
    int cs;
    int remove;
    while (true)
    {
        cs = menu();
        if (cs == 0) {
            break;
        }
        switch (cs) {
        case 1:
            read(path, list);
            break;
        case 2:
            list.InitList();
            writeAdd(path2, list.PrintFile(), "We added element");
            break;
        case 3:
            list.PrintAutolist();
            break;
        case 4:
            cout << "Номер элемента? ";
            cin >> remove;
            writeAdd(path2, list.PrintFile(remove), "We removed element");
            list.RemoveElement(remove);
            break;
        case 5:
            list.findAddres();
            break;
        case 6:
            write(path, list);
            break;
        default:
            break;
        }

    }
}