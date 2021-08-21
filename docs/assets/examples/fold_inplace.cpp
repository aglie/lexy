#include <deque>

#include <lexy/action/parse.hpp>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/file.hpp>
#include <lexy_ext/report_error.hpp>

namespace dsl = lexy::dsl;

//{
struct production
{
    static constexpr auto whitespace = dsl::ascii::space;

    static constexpr auto rule = [] {
        auto integer = dsl::integer<int>(dsl::digits<>);

        return dsl::list(integer, dsl::sep(dsl::comma));
    }();

    // Construct a `std::deque` in reverse order.
    static constexpr auto value
        = lexy::fold_inplace<std::deque<int>>(std::initializer_list<int>{},
                                              [](auto& deque, int i) { deque.push_front(i); });
};
//}

int main()
{
    auto input  = lexy::read_stdin<>().buffer();
    auto result = lexy::parse<production>(input, lexy_ext::report_error);
    if (!result)
        return 1;

    std::printf("numbers: ");
    for (auto i : result.value())
        std::printf("%d ", i);
    std::putchar('\n');
}
