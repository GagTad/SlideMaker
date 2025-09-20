#include <iostream>
#include <vector>
#include "Tokenizer.h"
#include "Parser.h"
#include "Command.h"

int main(int argc, char* argv[]) {
    // Ստուգում ենք՝ արդյոք օգտատերը որևէ հրաման մուտքագրել է
    if (argc < 2) {
        std::cout << "Օգտագործում։ ./presenter <հրաման> [պարամետրեր]" << std::endl;
        return 1;
    }

    // try...catch բլոկը կենտրոնական դեր ունի մեր Parser-ը ստուգելու համար
    try {
        // Քայլ 1: Թոքենիզացիա
        Tokenizer tokenizer;
        std::vector<Token> tokens = tokenizer.tokenize(argc, argv);
        
        // Քայլ 2: Վերլուծություն (ՍԱ ՔԵՐԱԿԱՆՈՒԹՅԱՆ ՍՏՈՒԳՈՒՄՆ Է)
        // Եթե քերականությունը սխալ է, այս տողը «սխալ կնետի» և կանցնի 'catch' բլոկին
        Parser parser(tokens);
        std::unique_ptr<Command> command = parser.parse();

        // Եթե ծրագիրը հասել է այս տողին, նշանակում է՝ վերլուծությունը հաջող է անցել
        std::cout << "✅ ՀԱՋՈՂՈՒԹՅՈՒՆ։ Հրամանի քերականությունը ճիշտ է։" << std::endl;

    } catch (const std::runtime_error& e) {
        // Եթե Parser-ը գտել է քերականական սխալ, ծրագիրը կանցնի այս հատվածին
        // e.what() ֆունկցիան ստանում է Parser-ի կողմից ուղարկված կոնկրետ սխալի հաղորդագրությունը
        std::cerr << "❌ ՍԽԱԼ։ " << e.what() << std::endl;
        return 1; // Ավարտել ծրագիրը սխալի կոդով
    }

    return 0; // Ավարտել ծրագիրը հաջողությամբ
}