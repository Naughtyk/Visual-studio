/////////////////////////////////////////////////////////////////////////////////////////
//Сеть Фейстеля.
/////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
/////////////////////////////////////////////////////////////////////////////////////////
typedef std::string                             T_str;
typedef unsigned int                            T_block_half;
typedef std::vector<T_block_half>               T_keys;
typedef std::pair<T_block_half, T_block_half>   T_block;
typedef std::vector<T_block>                    T_blocks;
/////////////////////////////////////////////////////////////////////////////////////////
const int   SIZEOF_BLOCK_HALF = sizeof(T_block_half);
const int   SIZEOF_BLOCK = SIZEOF_BLOCK_HALF * 2;
/////////////////////////////////////////////////////////////////////////////////////////
union  T_union
{
public:
    //-------------------------------------------------------------------------------
    char            symbols_[SIZEOF_BLOCK_HALF];
    //-------------------------------------------------------------------------------
    T_block_half    block_half_;
};
/////////////////////////////////////////////////////////////////////////////////////////
T_blocks  str_to_blocks(T_str  s)
{
    while (s.size() % SIZEOF_BLOCK != 0)
    {
        s.push_back(' ');
    }

    T_blocks  blocks;

    while (!s.empty())
    {
        T_str  str_L = s.substr(0, SIZEOF_BLOCK_HALF);
        s.erase(0, SIZEOF_BLOCK_HALF);

        T_union  union_L;

        for (size_t i = 0; i < str_L.size(); ++i)
        {
            union_L.symbols_[i] = str_L[i];
        }

        T_str  str_R = s.substr(0, SIZEOF_BLOCK_HALF);
        s.erase(0, SIZEOF_BLOCK_HALF);

        T_union  union_R;

        for (size_t i = 0; i < str_R.size(); ++i)
        {
            union_R.symbols_[i] = str_R[i];
        }

        blocks.push_back
        (
            std::make_pair
            (
                union_L.block_half_,
                union_R.block_half_
            )
        );
    }
    return  blocks;
}
/////////////////////////////////////////////////////////////////////////////////////////
T_str  blocks_to_str(const T_blocks& blocks)
{
    T_str  s_res;

    if (!blocks.empty())
    {
        for (T_blocks::const_iterator  block_it = blocks.begin();
            block_it != blocks.end(); ++block_it)
        {
            T_union     union_L;
            union_L.block_half_ = block_it->first;
            T_str       str_L;
            std::copy
            (
                union_L.symbols_,
                union_L.symbols_ + SIZEOF_BLOCK_HALF,
                std::back_inserter(str_L)
            );

            T_union     union_R;
            union_R.block_half_ = block_it->second;
            T_str       str_R;
            std::copy
            (
                union_R.symbols_,
                union_R.symbols_ + SIZEOF_BLOCK_HALF,
                std::back_inserter(str_R)
            );

            s_res += str_L + str_R;
        }
    }
    return  s_res;
}
/////////////////////////////////////////////////////////////////////////////////////////
T_block_half  f
(
    T_block_half    block_half,
    T_block_half    key
)
{
    return  block_half ^ key;
}
/////////////////////////////////////////////////////////////////////////////////////////
void feistel_encoding_block
(
    T_block& block,
    const T_keys& keys
)
{
    for (T_keys::const_iterator key_it = keys.begin(); ; ++key_it)
    {
        block.second ^= f(block.first, *key_it);
        if (key_it == keys.end() - 1) break;
        std::swap(block.first, block.second);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
void feistel_decoding_block
(
    T_block& block,
    const T_keys& keys
)
{
    for (T_keys::const_reverse_iterator key_rev_it = keys.rbegin(); ; ++key_rev_it)
    {
        block.second ^= f(block.first, *key_rev_it);
        if (key_rev_it == keys.rend() - 1) break;
        std::swap(block.first, block.second);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
T_blocks  feistel_encoding
(
    T_blocks        blocks,
    const T_keys& keys
)
{
    for (T_blocks::iterator  block_it = blocks.begin();
        block_it != blocks.end(); ++block_it)
    {
        feistel_encoding_block(*block_it, keys);
    }
    return  blocks;
}
/////////////////////////////////////////////////////////////////////////////////////////
T_blocks  feistel_decoding
(
    T_blocks        blocks,
    const T_keys& keys
)
{
    for (T_blocks::iterator  block_it = blocks.begin();
        block_it != blocks.end(); ++block_it)
    {
        feistel_decoding_block(*block_it, keys);
    }
    return  blocks;
}
/////////////////////////////////////////////////////////////////////////////////////////
T_keys  make_keys(int rounds_total)
{
    T_keys  keys;
    for (int i = 0; i < rounds_total; ++i)
    {
        long long  rand_val = rand() * rand() * rand();
        keys.push_back(T_block_half(rand_val));
    }
    return  keys;
}
/////////////////////////////////////////////////////////////////////////////////////////
void  print_blocks(const T_blocks& blocks)
{
    for (T_blocks::const_iterator  block_it = blocks.begin();
        block_it != blocks.end(); ++block_it)
    {
        std::cout << block_it->first
            << block_it->second
            << std::endl;
    }
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::locale::global(std::locale(""));
    srand(unsigned(time(0)));
    const int   ROUNDS_TOTAL = 10;

    T_keys      keys = make_keys(ROUNDS_TOTAL);
    std::cout << "Введите строку:"
        << std::endl;
    T_str       s;
    std::cin >> s;
    T_blocks   blocks = str_to_blocks(s);
    std::cout << "Блоки до зашифровки:"
        << std::endl;
    print_blocks(blocks);

    T_blocks  encoded_blocks = feistel_encoding(blocks, keys);
    std::cout << "Зашифрованные блоки:"
        << std::endl;
    print_blocks(encoded_blocks);

    T_blocks  decoded_blocks = feistel_decoding(encoded_blocks, keys);
    std::cout << "Расшифрованные блоки:"
        << std::endl;
    print_blocks(decoded_blocks);

    std::cout << "Расшифрованная строка:"
        << std::endl;

    T_str  decoded_s = blocks_to_str(decoded_blocks);
    std::cout << decoded_s
        << std::endl;
}