//
// Created by shadikanda on 10/19/19.
//
//  Wrapper design for dup command
//  proxy or decorator design for new & load
//  Decorator for slice (view), dup & catenated
//

#ifndef DNA_ANALYZER_CLI3_H
#define DNA_ANALYZER_CLI3_H

#include <map>
#include <list>
#include "dna_analyzer.h"
#include "dna_database.h"

typedef std::vector<DnaSequenceAnalyzer*> dna_vector;
typedef std::vector<std::string> VectorS;

//////////////////  Commands - Command Design Pattern  /////////////////////

class Command {
public:
    virtual void setup(VectorS str_vector, DataBase& db) = 0;
    virtual void execute() = 0;
};


/////////////////   Run Command - Command Design Pattern  ////////////////

class Run: public Command{
public:
    ~Run();
    void setup(VectorS str_vector, DataBase& db);
    void execute();
    DataBase getDB();
    static void updateQuit();
//    bool getQuit();

private:
    DataBase m_db;
    static bool m_quit;
    String m_cmd;
};

inline Run::~Run() {
}

inline DataBase Run::getDB() {
    return m_db;
}

inline void Run::updateQuit() {
    m_quit = !m_quit;
}

//inline bool Run::getQuit() {
//    return m_quit;
//}

////////////////////   End of: Run Command  ////////////////////

/*******************************************************************************/

///////////////   New Command - Command Design Pattern  ////////////////

class NewCommand: public Command {
public:
//    NewCommand(const String& dna_s, const String& name = "");
    NewCommand();
    ~NewCommand();
    void setup(VectorS str_vector, DataBase& db);
    void execute();
    DnaSequenceAnalyzer* getDnaA() ;

private:
    DnaSequenceAnalyzer *m_dna_a;
    DataBase* m_db;
    String m_dna_s;
    String m_name;
    String m_message_extra_args;
    String m_message_lack_args;
};

inline NewCommand::NewCommand() {
    m_message_extra_args = "Warning: extra arguments won't be taken in consideration!";
    m_message_lack_args = "Error: missing arguments! please enter the DNA sequence as a text & (optional) name for the"
                          " sequence: ";
}

inline NewCommand::~NewCommand(){
}

inline void NewCommand::setup(VectorS str_vec, DataBase& db) {
    size_t size = str_vec.size();
    if(size >= 2){
        m_dna_s = str_vec[1];
        m_db = &db;
        if(size > 3)
            std::cout << m_message_extra_args << std::endl;
        if(size >= 3)
            m_name = str_vec[2];
        else
            m_name = "";
    }
    else if(size == 1)
        std::cout << m_message_lack_args << std::endl;
}

inline void NewCommand::execute() {
    if(m_dna_s.getLen() != 0){ // !isDna
        m_dna_a = new DnaSequenceAnalyzer(m_dna_s, m_name);
        m_db->pushBack(m_dna_a);

        std::cout << *m_dna_a << std::endl;
    }
    else
        std::cout << "Error: invalid sequence" << std::endl;
}

inline DnaSequenceAnalyzer* NewCommand::getDnaA() {
    return m_dna_a;
}

////////////////////   End of: New Command  ////////////////////

/*******************************************************************************/

///////////////   Load Command - Command Design Pattern  ////////////////

class LoadCommand : public Command {
public:
//    LoadCommand(const char* path, const String& name = "");
    LoadCommand();
    ~LoadCommand();
    void setup(VectorS str_vec, DataBase& db);
    void execute();
    DnaSequenceAnalyzer* getDnaA() ;

private:
    DnaSequenceAnalyzer *m_dna_a;
    DataBase *m_db;
    const char* m_path;
    String m_name;
    String m_message_extra_args;
    String m_message_lack_args;
};

inline LoadCommand::LoadCommand() {
    m_message_extra_args = "Warning: extra arguments won't be taken in consideration!";
    m_message_lack_args = "Error: missing arguments! please enter the file's name as a text & (optional) name for the"
                          " sequence: ";
}

inline LoadCommand::~LoadCommand(){
}
inline void LoadCommand::setup(VectorS str_vec, DataBase& db) {
    size_t size = str_vec.size();

    if(size >= 2){
        m_path = str_vec[1].c_str();
        m_db = &db;

        if(size > 3)
            std::cout << m_message_extra_args << std::endl;
        if(size >= 3)
            m_name = str_vec[2];
        else
            m_name = str_vec[1];
    }

    else if(size == 1)
        std::cout << m_message_lack_args << std::endl;
}

inline void LoadCommand::execute() {

    m_dna_a = new DnaSequenceAnalyzer();
    m_dna_a->load(m_path, m_name);
    m_db->pushBack(m_dna_a);

    if(m_dna_a) // !isDna
        std::cout << m_dna_a->getDnaSequence() << std::endl;
    else
        std::cout << "Error: invalid sequence" << std::endl;
}

inline DnaSequenceAnalyzer *LoadCommand::getDnaA() {
    return m_dna_a;
}

////////////////////   End of: Load Command  ////////////////////

/*******************************************************************************/

//////////////////   Save Command - Command Design Pattern  ////////////////
class QuitCommand;   //forward declaration
class SaveCommand;
//class DnaObserver;
//class DnaStatusData;

//Base class for all observers
class Observer {
    friend class QuitCommand;    //     allow access to observedSubject
    friend class SaveCommand;    //     allow access to observedSubject

public:
    virtual bool quit(dna_vector& dna_v) = 0;
    virtual bool save(DnaSequenceAnalyzer& dna_a) = 0;

protected:
    Command *observedSubject;
};

class DnaObserver : public Observer
{
public:
    bool quit(dna_vector& dna_v);
    bool save(DnaSequenceAnalyzer& dna_a);
};

class SaveCommand : public Command {
public:
//    SaveCommand(const char* dna_id, DataBase db, const char* file_name = "");
    SaveCommand();
    ~SaveCommand();

    void addObserver(Observer * const _pObserver);
    void removeObserver(Observer * const _pObserver);
    void notifyObservers();

    void setup(VectorS str_vec, DataBase& db);
    void execute();
    DnaSequenceAnalyzer* getDnaA() ;

protected:
    Observer* m_comm;
    DnaSequenceAnalyzer *m_dna_a;
    const char* m_filename;
private:
    std::list<Observer *> m_registeredObservers;

    DataBase *m_db;
    size_t m_dna_id;
    String m_message_extra_args;
    String m_message_lack_args;
};

inline SaveCommand::SaveCommand() {
    m_message_extra_args = "Warning: extra arguments won't be taken in consideration!";
    m_message_lack_args = "Error: missing arguments! please enter the file's name as a text & (optional) name for the"
                          " sequence: ";
}

inline SaveCommand::~SaveCommand(){
    //  delete the observers
    std::list<Observer *>::iterator it = m_registeredObservers.begin();

    while (it != m_registeredObservers.end())
    {
        free(*it);
        it = m_registeredObservers.erase(it);
    }
}


inline void SaveCommand::addObserver(Observer * const _pObserver){
    _pObserver->observedSubject = this;
    m_registeredObservers.push_back(_pObserver);
}

inline void SaveCommand::removeObserver(Observer * const _pObserver){
    m_registeredObservers.remove(_pObserver);
    free(_pObserver);
}

inline void SaveCommand::notifyObservers(){
    std::list<Observer *>::iterator it = m_registeredObservers.begin();

    while (it != m_registeredObservers.end()){
        //  (*it)->save();  TODO: FIX
        it++;
    }
}


class FileStatus : public SaveCommand {
public:
    FileStatus(dna_vector& dna_v, Observer* observer);
    ~FileStatus();

    bool checkFileNameValidation() const;
    bool checkFileNameInDir() const;

    bool getValidation() const;
    bool getIsInDir() const;

private:
    bool m_is_name_valid;
    bool m_is_in_dir;
};

inline void SaveCommand::setup(VectorS str_vec, DataBase& db) {
    char temp[20];
    const char* dna_id;
    size_t id = 0;
    int flag = 0;
    dna_vector dna_v = db.getDnas();
    size_t size = str_vec.size();

    if(size >= 2){

        dna_id = str_vec[1].c_str();
        m_db = &db;
        memcpy(temp, dna_id + 1, strlen(dna_id) - 1);
        id = size_t(strtol(temp, NULL, 10));

        dna_vector::iterator it;
        for (it = dna_v.begin(); it != dna_v.end(); ++it)   {
            if(it.operator*()->getId() == id){
                m_dna_a = *it;
                flag = 1;
            }
        }

        if(!flag){
            std::cout << "Error: there is no such dna!" << std::endl;
            return;
        }

        if(size >= 3) {
            m_filename = str_vec[2].c_str();
            if (size > 3)
                std::cout << m_message_extra_args << std::endl;
        }
        else
            m_filename = "";
    }

    else if(size == 1)
        std::cout << m_message_lack_args << std::endl;
}

inline void SaveCommand::execute() {
    if(m_dna_a) // !isDna
        m_dna_a->save(m_filename);
    else
        std::cout << "Error: invalid sequence" << std::endl;
}

inline DnaSequenceAnalyzer *SaveCommand::getDnaA() {
    return m_dna_a;
}

inline FileStatus::~FileStatus() {
}

inline bool FileStatus::getValidation() const {
    return m_is_name_valid;
}

inline bool FileStatus::getIsInDir() const {
    return m_is_in_dir;
}

inline bool FileStatus::checkFileNameValidation() const {
    return false;
}

inline bool FileStatus::checkFileNameInDir() const {
    return false;
}

inline FileStatus::FileStatus(dna_vector &dna_v, Observer *observer) {
    m_comm = observer;
    m_is_name_valid = true;
    m_is_in_dir = false;
}

inline bool DnaObserver::save(DnaSequenceAnalyzer& dna_a) {
    FileStatus* p_save = static_cast<FileStatus*>(observedSubject);
    p_save->checkFileNameValidation();
    p_save->checkFileNameInDir();

//    if(p_save->getModified() == 0 && p_save->getNew() == 0){
//        std::cout << "Thank you for using Dnalanyzer." << "\nGoodbye! " << std::endl;
//        Run::updateQuit();
//        return true;
//    }

//    std::cout << "There are " << p_quit->getModified() << " modified and " << p_quit->getNew() <<
//              " new sequences. Are ""you sure you want to quit?" << std::endl;
//    std::cout << "Please confirm by 'y' or 'Y', or cancel by 'n' or 'N'." << std::endl;

    while (true) {
        std::string tmp;
        std::cout << "> confirm >>> ";
        std::cin >> tmp;
        const char* temp = tmp.c_str();

        if (!strcmp(temp, "Y") || !strcmp(temp, "y")) {
            std::cout << "Thank you for using Dnalanyzer." << "\nGoodbye! " << std::endl;
            Run::updateQuit();
            return true;
        }
        if (!strcmp(temp, "N") || !strcmp(temp, "n"))
            return false;
        else
            std::cout << "You have typed an invalid response. Please either confirm by 'y'/'Y', or cancel by "
                         "'n'/'N'." << std::endl;
    }
}

////////////////////   End of: Save Command  ////////////////////

/*******************************************************************************/

////////////////   Quit Command - Observer Design Pattern  ///////////////////


class QuitCommand : public Command {

public:
    QuitCommand();
    ~QuitCommand();
    void addObserver(Observer * const _pObserver);
    void removeObserver(Observer * const _pObserver);
    void notifyObservers();

    void setup(VectorS str_vec, DataBase& db);
    void execute();

    void updateExit();
    bool getExit();

protected:
    Observer* m_comm;
    dna_vector m_dna_v;
private:
    std::list<Observer *> m_registeredObservers;
    DataBase* m_db;
    bool m_exit;
};

inline QuitCommand::QuitCommand(){
    m_exit = false;
}

class DnaStatusData : public QuitCommand {
public:
    DnaStatusData(dna_vector& dna_v, Observer* observer);
    ~DnaStatusData();
    size_t getUpToDate() const;
    size_t getNew() const;
    size_t getModified() const;

    void updateStatus(dna_vector& dna_v);

private:
    size_t m_up_to_date;
    size_t m_new;
    size_t m_modified;
};

inline QuitCommand::~QuitCommand(){
    //  delete the observers
    std::list<Observer *>::iterator it = m_registeredObservers.begin();

    while (it != m_registeredObservers.end())
    {
        free(*it);
        it = m_registeredObservers.erase(it);
    }
}

inline void QuitCommand::addObserver(Observer * const _pObserver){
    _pObserver->observedSubject = this;
    m_registeredObservers.push_back(_pObserver);
}

inline void QuitCommand::removeObserver(Observer * const _pObserver){
    m_registeredObservers.remove(_pObserver);
    free(_pObserver);
}

inline void QuitCommand::notifyObservers(){
    std::list<Observer *>::iterator it = m_registeredObservers.begin();

    while (it != m_registeredObservers.end()){
        (*it)->quit(m_dna_v);
        it++;
    }
}

inline void QuitCommand::setup(VectorS str_vec, DataBase &db) {
    Observer* pObserver = new DnaObserver();

    m_dna_v = static_cast<dna_vector>(0);
    m_comm = pObserver;
    m_db = &db;
    m_dna_v = db.getDnas();
}

inline void QuitCommand::execute() {
    DnaStatusData dnaStatusData(m_dna_v, m_comm);
    dnaStatusData.addObserver(m_comm);
    dnaStatusData.notifyObservers();
}

inline bool QuitCommand::getExit() {
    return m_exit;
}

inline void QuitCommand::updateExit() {
    m_exit = !m_exit;
//    m_quit
}


inline DnaStatusData::DnaStatusData(dna_vector& dna_v, Observer* observer) : QuitCommand() {
    m_new = 0;
    m_modified = 0;
    m_up_to_date = 0;
    m_dna_v = dna_v;
    m_comm = observer;
}

inline DnaStatusData::~DnaStatusData(){
}

inline size_t DnaStatusData::getUpToDate () const{
    return m_up_to_date;
}

inline size_t DnaStatusData::getNew () const{
    return m_new;
}

inline size_t DnaStatusData::getModified () const{
    return m_modified;
}

inline void DnaStatusData::updateStatus(dna_vector& dna_v){
    String temp;
    dna_vector::iterator it;
    for (it = dna_v.begin(); it != dna_v.end(); ++it) {   //  for testing
        temp = it.operator*()->getStatus();
        if(!my_strcmp(temp, "up to date"))
            ++m_up_to_date;
        else if(!my_strcmp(temp, "new"))
            ++m_new;
        else
            ++m_modified;
    }
}

inline bool DnaObserver::quit(dna_vector& dna_v) {
    DnaStatusData* p_quit = static_cast<DnaStatusData*>(observedSubject);
    p_quit->updateStatus(dna_v);

    if(p_quit->getModified() == 0 && p_quit->getNew() == 0){
        std::cout << "Thank you for using Dnalanyzer." << "\nGoodbye! " << std::endl;
        Run::updateQuit();
        return true;
    }

    std::cout << "There are " << p_quit->getModified() << " modified and " << p_quit->getNew() <<
              " new sequences. Are ""you sure you want to quit?" << std::endl;
    std::cout << "Please confirm by 'y' or 'Y', or cancel by 'n' or 'N'." << std::endl;

    while (true) {
        std::string tmp;
        std::cout << "> confirm >>> ";
        std::cin >> tmp;
        const char* temp = tmp.c_str();

        if (!strcmp(temp, "Y") || !strcmp(temp, "y")) {
            std::cout << "Thank you for using Dnalanyzer." << "\nGoodbye! " << std::endl;
            Run::updateQuit();
            return true;
        }
        if (!strcmp(temp, "N") || !strcmp(temp, "n"))
            return false;
        else
            std::cout << "You have typed an invalid response. Please either confirm by 'y'/'Y', or cancel by "
                         "'n'/'N'." << std::endl;
    }
}

//////////////////////   End of: Quit Command  ////////////////////
//
///*******************************************************************************/
//
/////////////////////   Show Command & List Command - Data Access Object Design Pattern  ///////////////////


class DnaDao{
    friend class ShowCommand;
public:
    virtual void printShowDna(const char *length) = 0;
    virtual void printListDna() = 0;
};

class DnaDaoImp: public DnaDao{
    friend class ShowCommand;

public:
    DnaDaoImp(DnaSequenceAnalyzer* dna_a);
    DnaDaoImp(dna_vector dna_v);
    ~DnaDaoImp();
    void printShowDna(const char *length);
    void printListDna();

private:
    DnaSequenceAnalyzer* m_dna_a;
    dna_vector m_dna_v;
};


inline DnaDaoImp::DnaDaoImp(DnaSequenceAnalyzer* dna_a) {
    m_dna_a = dna_a;
}

inline DnaDaoImp::DnaDaoImp(dna_vector dna_v) {
    m_dna_v = dna_v;
    m_dna_a = NULL;
}

inline DnaDaoImp::~DnaDaoImp() {
}

inline void DnaDaoImp::printShowDna(const char *length) {
    char temp[20];

    size_t len = 0, i = 0, size = m_dna_a->getDnaSequence().getLen();
    std::ostream& os = std::cout;
    memcpy(temp, length, strlen(length));
    len = size_t(strtol(temp, NULL, 10));

    os << "[" << m_dna_a->getId() << "] " << m_dna_a->getName() << ' ' << m_dna_a->getStatus();
    for(; i < len && i < size; ++i){
        if(!(i%99))
            os << '\n';
        os << m_dna_a->getDnaSequence()[i].getNuc();
    }
    os << std::endl;
}

////////////////////      Show Command    ///////////////////////

class ShowCommand : public Command{
public:
    ShowCommand();
    ~ShowCommand();
    void setup(VectorS str_vec, DataBase& db);
    void execute();

private:
    DnaSequenceAnalyzer* m_dna_a;
    const char *m_length;
    DataBase *m_db;
    String m_message_extra_args;
    String m_message_lack_args;
};

inline ShowCommand::ShowCommand() {
    m_message_extra_args = "Warning: extra arguments won't be taken in consideration!";
    m_message_lack_args = "Error: missing arguments! please enter the sequence's id (with # at the beginning)"
                          " & (optional) number of first nucleotides you want to show (default = 99)";
}

inline ShowCommand::~ShowCommand() {
}

inline void ShowCommand::setup(VectorS str_vec, DataBase &db) {
    size_t size = str_vec.size();
    char temp[20];
    size_t id = 0;
    int flag = 0;
    dna_vector dna_v;

    if(size >= 2){
        const char* dna_id = str_vec[1].c_str();
        memcpy(temp, dna_id + 1, strlen(dna_id) - 1);
        id = size_t(strtol(temp, NULL, 10));
        m_db = &db;
        dna_v = m_db->getDnas();
        dna_vector::iterator it;
        for (it = dna_v.begin(); it != dna_v.end(); ++it)   {
            if(it.operator*()->getId() == id){
                m_dna_a = *it;
                flag = 1;
            }
        }
        if(!flag)
            std::cout << "Error: there is no such dna!" << std::endl;

        if(size > 3 && flag)
            std::cout << m_message_extra_args << std::endl;
        if(size >= 3)
            m_length = str_vec[2].c_str();
        else
            m_length = "99";
    }

    else if(size == 1){
        std::cout << m_message_lack_args << std::endl;
        m_dna_a = NULL;
    }
}

inline void ShowCommand::execute() {
    if(m_dna_a != NULL){
        DnaDao* dna_show = new DnaDaoImp(m_dna_a);
        dna_show->printShowDna(m_length);
    }
}

//////////////////////   End of: Show Command  ////////////////////
//
//////////////////////      List Command    ///////////////////////


class ListCommand : public Command{
public:
    ListCommand();
    ~ListCommand();
    void setup(VectorS str_vec, DataBase& db);
    void execute();

private:
    dna_vector m_dna_v;
    String m_message_extra_args;
    String m_message_empty;
};

inline ListCommand::ListCommand() {
    m_message_extra_args = "Warning: extra arguments won't be taken in consideration!";
    m_message_empty = "Sorry, there are no DNAs!";
}

inline ListCommand::~ListCommand() {
}

inline void ListCommand::setup(VectorS str_vec, DataBase &db) {
    size_t size = str_vec.size();
    m_dna_v = db.getDnas();

    if(size > 1)
        std::cout << m_message_extra_args << std::endl;
}

inline void ListCommand::execute() {
    if(!m_dna_v.empty()){
        DnaDao* dna_list = new DnaDaoImp(m_dna_v);
        dna_list->printListDna();
    }
    else{
        std::cout << m_message_empty << std::endl;
    }
}

inline void DnaDaoImp::printListDna() {
    size_t i, size;
    const char n = 'n', m = 'm', u = 'u';
    std::map<const char, char> prefix;
    std::ostream& os = std::cout;
    dna_vector::iterator it;

    prefix.insert(std::pair<const char, char>(n, 'o'));
    prefix.insert(std::pair<const char, char>(m, '*'));
    prefix.insert(std::pair<const char, char>(u, '-'));

    for (it = m_dna_v.begin(); it != m_dna_v.end(); ++it){
        m_dna_a = *it;
        size = m_dna_a->getDnaSequence().getLen();

        os << prefix.at(m_dna_a->getStatus()[0]) << " [" << m_dna_a->getId() << "] " << m_dna_a->getName() << ":\n";

        for(i = 0; i < 40 && i < size; ++i){
            os << m_dna_a->getDnaSequence()[i].getNuc();
        }
        os << "\n";
    }
}

//////////////////////   End of: List Command  ////////////////////
//
///*******************************************************************************/

typedef std::map<std::string, Command*> CommandsMap;

class CommandFactory
{
public:
//    CommandFactory();
    ~CommandFactory();
    static void setup();
    Command* makeCommand(const std::string& cmd) const;

private:
    static bool isSetup;
    static CommandsMap creators;
};

//inline CommandFactory::CommandFactory() {
//    isSetup = false;
//
//}
inline Command* CommandFactory::makeCommand(const std::string& cmd) const    //  TODO: check const stuff here
{
    Command*  fn = creators[cmd];
    if (fn == NULL) {
//        throw ("Command not found: ");
        return NULL;
    }
    return fn; // Call lambda and return new unique pointer.
}

inline void CommandFactory::setup() {
    if (isSetup) {
        // Run setup only once.
        return;
    }
    isSetup = true;

    // Clear creators.
    creators.clear();

    creators["new"] = (new NewCommand());
    creators["load"] = (new LoadCommand());
    creators["save"] = (new SaveCommand());
    creators["show"] = (new ShowCommand());
    creators["list"] = (new ListCommand());
    creators["quit"] = (new QuitCommand());


}


inline CommandFactory::~CommandFactory() {

}
/*********************************    End    ***********************************/


#endif //DNA_ANALYZER_CLI3_H
