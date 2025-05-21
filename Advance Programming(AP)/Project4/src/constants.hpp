#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <vector>

const std::string CREATE_TEMP = "create_template";
const std::string GENERATE_TEST = "generate_test";
const std::string ATTEND = "attend";
const std::string AUTO_GENERATE = "auto_generate";
const std::string REPORT = "report";
const std::string ALL = "all";
const std::string TEST = "test";
const std::string TESTS = "tests";
const std::string SUBJECT = "subject";
const std::string QUESTION_TEXT = "question_text";
const std::string OPTION1 = "option1";
const std::string OPTION2 = "option2";
const std::string OPTION3 = "option3";
const std::string OPTION4 = "option4";
const std::string CORRECT_ANS = "correct ans";
const std::string NUM_INCORRECTS = "numOfIncorrects";
const std::string NUM_BLANKS = "numOfBlanks";
const std::string NUM_CORRECTS = "numOfCorrects";
const std::string EASY = "easy";
const std::string MEDIUM = "medium";
const std::string HARD = "hard";
const std::string EASY_ = "Easy";
const std::string MEDIUM_ = "Medium";
const std::string HARD_ = "Hard";
const std::vector<std::string> DIFFICULTY = {EASY, MEDIUM, HARD};

const std::string TAB = "    ";
const std::string FLASH = " <-";
const std::vector<std::vector<std::string>> NONE_VECTOR = {{"NONE", "NONE"}};

#endif 