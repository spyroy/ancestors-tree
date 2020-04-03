#include "FamilyTree.hpp"
#include "doctest.h"
#include <string>

using namespace std;
using namespace family;

Tree BuildTree(){
    Tree T("matan");
    T.addFather("matan", "uri");
    T.addFather("uri", "haim");
    T.addFather("haim", "leiv");
    T.addFather("leiv", "avraham");
    T.addFather("avraham", "adam");
    T.addMother("matan", "orli");
    T.addMother("orli", "tirzza");
    T.addMother("tirzza", "bella");
    T.addMother("bella", "sarah");
    T.addMother("sarah", "eve");
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
}


TEST_CASE("add father"){
    Tree T("matan");
    CHECK(T.addFather("matan", "uri") == Tree("uri"));
    CHECK(T.addFather("uri", "haim") == Tree("haim"));
    CHECK(T.addFather("haim", "leiv") == Tree("leiv"));
    CHECK_THROWS(T.addFather("matan", "leiv"));
    CHECK_THROWS(T.addFather("matan", "haim"));
    CHECK_THROWS(T.addFather("matan", "uri"));
    CHECK_THROWS(T.addFather("uri", "matan"));
    CHECK_THROWS(T.addFather("matan", "matan"));
    CHECK_THROWS(T.addFather("matan", "uri"));
    CHECK_THROWS(T.addFather("mec", "moshe"));
}

TEST_CASE("add mother"){
    Tree T("matan");
    CHECK(T.addMother("matan", "orli") == Tree("orli"));
    CHECK(T.addMother("orli", "tirzza") == Tree("tirzza"));
    CHECK(T.addMother("tirzza", "bella") == Tree("bella"));
    CHECK_THROWS(T.addFather("matan", "tirzza"));
    CHECK_THROWS(T.addFather("matan", "bella"));
    CHECK_THROWS(T.addFather("matan", "orli"));
    CHECK_THROWS(T.addFather("orli", "matan"));
    CHECK_THROWS(T.addFather("matan", "matan"));
    CHECK_THROWS(T.addFather("matan", "orli"));
    CHECK_THROWS(T.addFather("mec", "sarah"));
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
    CHECK(T.relation("adam") == string("great-great-graet-grandfather"));
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
    Tree T = BuildTree();
    CHECK(T.find("me") == string("matan"));
    CHECK(T.find("father") == string("uri"));
    CHECK(T.find("grandfather") == string("haim"));
    CHECK(T.find("great-grandfather") == string("leiv"));
    CHECK(T.find("great-great-grandfather") == string("avraham"));
    CHECK(T.find("great-great-great-grandfather") == string("adam"));
    CHECK(T.find("mother") == string("orli"));
    CHECK(T.relation("grandmother") == string("tirzza"));
    CHECK(T.relation("great-grandmother") == string("bella"));
    CHECK(T.relation("great-great-grandmother") == string("sarah"));
    CHECK(T.relation("great-great-great-grandmother") == string("eve"));
    CHECK_THROWS(T.relation("great-great-great-great-grandmother"));
    CHECK_THROWS(T.relation("grand-grandmother"));
    CHECK_THROWS(T.relation("sister"));
    CHECK_THROWS(T.relation("brother"));
    CHECK_THROWS(T.relation("greatmother"));
    CHECK_THROWS(T.relation("greatfather"));
    CHECK_THROWS(T.relation("grand-grandfather"));
}

TEST_CASE("remove"){
    Tree T = BuildTree();
    T.remove("me");
    CHECK(T.relation("me") == string("unrelated"));
    CHECK(T.relation("uri") == string("unrelated"));
    CHECK(T.relation("haim") == string("unrelated"));
    CHECK(T.relation("leiv") == string("unrelated"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("unrelated"));
    CHECK(T.relation("tirzza") == string("unrelated"));
    CHECK(T.relation("bella") == string("unrelated"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("uri");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("unrelated"));
    CHECK(T.relation("haim") == string("unrelated"));
    CHECK(T.relation("leiv") == string("unrelated"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("graet-great-great-grandmother"));
    T = BuildTree();
    T.remove("orli");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("graet-great-great-grandfather"));
    CHECK(T.relation("orli") == string("unrelated"));
    CHECK(T.relation("tirzza") == string("unrelated"));
    CHECK(T.relation("bella") == string("unrelated"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("haim");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("unrelated"));
    CHECK(T.relation("leiv") == string("unrelated"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("graet-great-great-grandmother"));
    T = BuildTree();
    T.remove("tirzza");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("graet-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("unrelated"));
    CHECK(T.relation("bella") == string("unrelated"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("leiv");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("unrelated"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("graet-great-great-grandmother"));
    T = BuildTree();
    T.remove("bella");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("graet-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("unrelated"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("avraham");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("unrelated"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("graet-great-great-grandmother"));
    T = BuildTree();
    T.remove("sarah");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("graet-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("unrelated"));
    CHECK(T.relation("eve") == string("unrelated"));
    T = BuildTree();
    T.remove("adam");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("unrelated"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("graet-great-great-grandmother"));
    T = BuildTree();
    T.remove("eve");
    CHECK(T.relation("me") == string("me"));
    CHECK(T.relation("uri") == string("father"));
    CHECK(T.relation("haim") == string("grandfather"));
    CHECK(T.relation("leiv") == string("great-grandfather"));
    CHECK(T.relation("avraham") == string("great-great-grandfather"));
    CHECK(T.relation("adam") == string("graet-great-great-grandfather"));
    CHECK(T.relation("orli") == string("mother"));
    CHECK(T.relation("tirzza") == string("grandmother"));
    CHECK(T.relation("bella") == string("great-grandmother"));
    CHECK(T.relation("sarah") == string("great-great-grandmother"));
    CHECK(T.relation("eve") == string("unrelated"));

}