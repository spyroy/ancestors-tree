#include "FamilyTree.hpp"
#include "doctest.h"
#include <string>

using namespace std;
using namespace family;

Tree BuildTree(){
    Tree T("matan");
    CHECK_NOTHROW(T.addFather("matan", "uri"));
    CHECK_NOTHROW(T.addFather("uri", "haim"));
    CHECK_NOTHROW(T.addFather("haim", "leiv"));
    CHECK_NOTHROW(T.addFather("leiv", "avraham"));
    CHECK_NOTHROW(T.addFather("avraham", "adam"));
    CHECK_NOTHROW(T.addMother("matan", "orli"));
    CHECK_NOTHROW(T.addMother("orli", "tirzza"));
    CHECK_NOTHROW(T.addMother("tirzza", "bella"));
    CHECK_NOTHROW(T.addMother("bella", "sarah"));
    CHECK_NOTHROW(T.addMother("sarah", "eve"));
    return T;
}

Tree BuildComplicatedTree(){
    Tree T("matan");
    CHECK_NOTHROW(T.addFather("matan", "uri"));
    CHECK_NOTHROW(T.addMother("matan", "orli"));
    CHECK_NOTHROW(T.addFather("uri", "haim"));
    CHECK_NOTHROW(T.addMother("uri", "ora"));
    CHECK_NOTHROW(T.addFather("orli", "moshe"));
    CHECK_NOTHROW(T.addMother("orli", "tirzza"));
    CHECK_NOTHROW(T.addFather("haim", "leiv"));
    CHECK_NOTHROW(T.addMother("haim", "rivka"));
    CHECK_NOTHROW(T.addFather("ora", "eliezer"));
    CHECK_NOTHROW(T.addMother("ora", "rachal"));
    CHECK_NOTHROW(T.addFather("moshe", "adam"));
    CHECK_NOTHROW(T.addMother("moshe", "eve"));
    CHECK_NOTHROW(T.addFather("tirzza", "eliezer"));
    CHECK_NOTHROW(T.addMother("tirzza", "bella"));
    return T;
}

Tree BuildTwistedTree(){
    Tree T("or");
    CHECK_NOTHROW(T.addFather("or", "tzvika"));
    CHECK_NOTHROW(T.addMother("or", "sigal"));
    CHECK_NOTHROW(T.addFather("tzvika", "moti"));
    CHECK_NOTHROW(T.addMother("tzvika", "frida"));
    CHECK_NOTHROW(T.addFather("sigal", "moshe"));
    CHECK_NOTHROW(T.addMother("sigal", "aviva"));
    CHECK_NOTHROW(T.addFather("moshe", "meir"));
    CHECK_NOTHROW(T.addMother("moshe", "rivka"));
    CHECK_NOTHROW(T.addFather("aviva", "eli"));
    CHECK_NOTHROW(T.addMother("aviva", "sofi"));
    CHECK_NOTHROW(T.addFather("sofi", "josh"));
    CHECK_NOTHROW(T.addMother("sofi", "nicole"));
    CHECK_NOTHROW(T.addFather("moti", "boris"));
    CHECK_NOTHROW(T.addMother("moti", "shelima"));
    return T;
}


TEST_CASE("add father"){
    Tree T("matan");
    CHECK_NOTHROW(T.addFather("matan", "uri"));
    CHECK_NOTHROW(T.addFather("uri", "haim"));
    CHECK_NOTHROW(T.addFather("haim", "leiv"));
    CHECK_THROWS(T.addFather("matan", "leiv"));
    CHECK_THROWS(T.addFather("matan", "haim"));
    CHECK_THROWS(T.addFather("matan", "uri"));
    CHECK_THROWS(T.addFather("matan", "matan"));
    CHECK_THROWS(T.addFather("matan", "uri"));
    CHECK_THROWS(T.addFather("mec", "moshe"));
}

TEST_CASE("add mother"){
    Tree T("matan");
    CHECK_NOTHROW(T.addMother("matan", "orli"));
    CHECK_NOTHROW(T.addMother("orli", "tirzza"));
    CHECK_NOTHROW(T.addMother("tirzza", "bella"));
    CHECK_THROWS(T.addMother("matan", "tirzza"));
    CHECK_THROWS(T.addMother("matan", "bella"));
    CHECK_THROWS(T.addMother("matan", "orli"));
    CHECK_THROWS(T.addMother("orli", "matan"));
    CHECK_THROWS(T.addMother("matan", "matan"));
    CHECK_THROWS(T.addMother("matan", "orli"));
    CHECK_THROWS(T.addMother("mec", "sarah"));
}

TEST_CASE("display"){
    Tree T = BuildTree();
    T.display();
    Tree CT = BuildComplicatedTree();
    CT.display();
}

TEST_CASE("relation"){
    Tree T = BuildTree();
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("great-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("great-great-great-grandmother"));
    CHECK(T.relation("izzhak") == string("unrelated"));
    CHECK(T.relation("yaakov") == string("unrelated"));
    CHECK(T.relation("moshe") == string("unrelated"));
}

TEST_CASE("find"){
    Tree T = BuildTree();//T is matan aka - me
    CHECK(T.find("me") == string("matan"));
    CHECK(T.find("father") == string("uri"));
    CHECK(T.find("grandfather") == string("haim"));
    CHECK(T.find("great-grandfather") == string("leiv"));
    CHECK(T.find("great-great-grandfather") == string("avraham"));
    CHECK(T.find("great-great-great-grandfather") == string("adam"));
    CHECK(T.find("mother") == string("orli"));
    CHECK(T.find("grandmother") == string("tirzza"));
    CHECK(T.find("great-grandmother") == string("bella"));
    CHECK(T.find("great-great-grandmother") == string("sarah"));
    CHECK(T.find("great-great-great-grandmother") == string("eve"));
    CHECK_THROWS(T.find("great-great-great-great-grandmother"));
    CHECK_THROWS(T.find("grand-grandmother"));
    CHECK_THROWS(T.find("sister"));
    CHECK_THROWS(T.find("brother"));
    CHECK_THROWS(T.find("greatmother"));
    CHECK_THROWS(T.find("greatfather"));
    CHECK_THROWS(T.find("grand-grandfather"));
    Tree T2 = BuildComplicatedTree();
    CHECK(T.find("me") == string("matan"));
    CHECK(T.find("father") == string("uri"));
    CHECK(T.find("mother") == string("orli"));
    CHECK((T.find("grandfather") == string("haim") || T.find("grandfather") == string("moshe")));
    CHECK((T.find("grandmother") == string("tirzza") || T.find("grandmother") == string("ora")));
    CHECK((T.find("great-grandfather") == string("leiv") || T.find("great-grandfather") == string("eliezer") || T.find("great-grandfather") == string("adam")));
    CHECK((T.find("great-grandmother") == string("bella") || T.find("great-grandmother") == string("eve") || T.find("great-grandmother") == string("rachel") || T.find("great-grandmother") == string("rivka")));
}

TEST_CASE("remove"){
    Tree T = BuildTree();
    // T.remove("matan");
    // CHECK(T.relation("matan") == string("unrelated"));
    // CHECK(T.relation("uri") == string("unrelated"));
    // CHECK(T.relation("haim") == string("unrelated"));
    // CHECK(T.relation("leiv") == string("unrelated"));
    // CHECK(T.relation("avraham") == string("unrelated"));
    // CHECK(T.relation("adam") == string("unrelated"));
    // CHECK(T.relation("orli") == string("unrelated"));
    // CHECK(T.relation("tirzza") == string("unrelated"));
    // CHECK(T.relation("bella") == string("unrelated"));
    // CHECK(T.relation("sarah") == string("unrelated"));
    // CHECK(T.relation("eve") == string("unrelated"));
    CHECK_THROWS(T.remove("matan"));
    T.remove("uri");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("unrelated"));
    CHECK(T.relation("haim") == string("unrelated"));
    CHECK(T.relation("leiv") == string("unrelated"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("great-great-great-grandmother"));
    T = BuildTree();
    T.remove("orli");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("great-great-great-grandfather"));
    CHECK(T.relation("orli") == string("unrelated"));
    CHECK(T.relation("tirzza") == string("unrelated"));
    CHECK(T.relation("bella") == string("unrelated"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("haim");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("unrelated"));
    CHECK(T.relation("leiv") == string("unrelated"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("great-great-great-grandmother"));
    T = BuildTree();
    T.remove("tirzza");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("great-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("unrelated"));
    CHECK(T.relation("bella") == string("unrelated"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("leiv");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("unrelated"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("great-great-great-grandmother"));
    T = BuildTree();
    T.remove("bella");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("great-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("unrelated"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("avraham");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("great-great-great-grandmother"));
    T = BuildTree();
    T.remove("sarah");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("great-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("adam");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("great-great-great-grandmother"));
    T = BuildTree();
    T.remove("eve");
    CHECK(T.relation("matan") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("great-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("unrelated"));
    CHECK_THROWS(T.remove("bla"));
}
TEST_CASE("Exceptions")
{
    Tree ex=BuildTwistedTree();
    CHECK_THROWS(ex.remove("or"));
    CHECK_FALSE(ex.relation("or") == string("unrelated"));
    CHECK(ex.relation("nicole") == string("great-great-grandmother"));//Should be true
    ex.remove("sofi");
    CHECK(ex.relation("sofi") == string("unrelated"));
    CHECK(ex.relation("josh") == string("unrelated"));
    CHECK(ex.relation("nicole") == string("unrelated"));
    CHECK_NOTHROW(ex.addFather("frida", "meir"));//Or has two great-grandfathers named meir
    CHECK_NOTHROW(ex.display()); 
}
