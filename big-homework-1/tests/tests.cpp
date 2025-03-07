//#include "../third_party/googletest/googletest/include/gtest/gtest.h"
//#include "../database/decorator/Facade.h"
//#include "../src/executor/commands_implementation/AddAccount.h"
//#include "../src/executor/commands_implementation/AddCategory.h"
//#include "../src/executor/commands_implementation/ApplyPayment.h"
//#include "../src/executor/commands_implementation/GetAccounts.h"
//#include "../src/executor/commands_implementation/TopUpAccount.h"
//#include "../src/executor/commands_implementation/DeleteAccount.h"
//#include "../src/factory/CommandFactory.h"
//#include "../src/helper.h"
//// так в общем все функции реализованы скорее в void формате, будем тестировать приложение, тестируя работу
//// базы данных, ведь по сути она отражает всю суть и что все корректно отрабатывает
//// короче тесты будут скорее интеграционными, будем рисовать полные пользовательские сценарии
//
//TEST(AddAccount, DatabaseFacade) {
//    DatabaseFacade db("dbname=finance_tracker host=localhost port=5432");
//    db.Init("../database/migrations/init_db.sql");
//
//    std::string account_name = "test_account";
//
//    std::string query = "SELECT * FROM finance_tracker.bank_account WHERE account_name = $1";
//    std::vector<std::string> params = {account_name};
//    pqxx::result res = db.ExecuteQuery(query, params);
//
//    ASSERT_EQ(res.size(), 1);
//    ASSERT_EQ(res[0]["account_name"].as<std::string>(), account_name);
//}