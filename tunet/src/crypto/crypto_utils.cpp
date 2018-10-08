//
// Created by Hippolyte Barraud on 10/10/18.
//

/*
 * This is a (very) rough cpp equivalent to the JS xEncode function used as part of the credential hashing process
 * by Tsinghua network.
 *
 * I have no idea what it does.
 */

#include <crypto/crypto_utils.hpp>
#include <boost/algorithm/string/join.hpp>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

auto s(boost::string_view a, bool b) {
    auto c = a.size();
    std::vector<int> v;
    for (std::size_t i = 0; i < c; i += 4) {
        int elem = a[i];
        if (i + 1 < a.size())
            elem |= a[i + 1]<< 8;
        if (i + 2 < a.size())
            elem |= a[i + 2] << 16;
        if (i + 3 < a.size())
            elem |= a[i + 3] << 24;
        v.emplace_back(elem);
    }
    if (b) {
        v.emplace_back(c);
    }
    return v;
}

auto l(std::vector<int> a, bool b) {
    std::vector<std::u16string> a2(a.size());
    auto d = a.size();
    auto c = (d - 1) << 2;

    if (b) {
        auto m = (int)a[d - 1];
        if ((m < (int)c - 3) || (m > (int)c))
            return std::u16string();
        c = static_cast<size_t >(m);
    }
    for (auto i = 0; (size_t)i < d; i++) {
        a2[i] = std::u16string(4, '\0');
        a2[i][0] = static_cast<char16_t>(a[i] & 0xff);
        a2[i][1] = static_cast<char16_t>(a[i] >> 8 & 0xff);
        a2[i][2] = static_cast<char16_t>(a[i] >> 16 & 0xff);
        a2[i][3] = static_cast<char16_t>(a[i] >> 24 & 0xff);
    }
    if (b) {
        return boost::algorithm::join(a2, "").substr(0, c);
    } else {
        return boost::algorithm::join(a2, "");
    }
}

std::string xEncode(boost::string_view str, boost::string_view key) {
    if (str.empty()) {
        return std::string();
    }
    auto v = s(str, true);
    auto k = s(key, false);
    if (k.size() < 4) {
        k.resize(4);
    }
    auto n = v.size() - 1;
    auto z = v[n];
    auto y = 0;
    int c = 0x86014019 | 0x183639A0;
    int64_t m = 0;
    auto e = 0;
    auto p = 0;
    auto q = 6 + 52 / (n + 1);
    auto d = 0;
    while (0 < q--) {
        d = (d + c) & (0x8CE0D9BF | 0x731F2640);
        e = d >> 2 & 3;
        for (p = 0; (size_t)p < n; p++) {
            y = v[p + 1];
            m = (uint32_t)z >> 5 ^ (uint32_t)y << 2;
            m += ((uint32_t)y >> 3 ^ z << 4) ^ (d ^ y);
            m += k[(p & 3) ^ e] ^ z;
            z = v[p] = (static_cast<int>(v[p] + m) & (0xEFB8D130 | 0x10472ECF));
        }
        y = v[0];
        m = (uint32_t)z >> 5 ^ y << 2;
        m += ((uint32_t)y >> 3 ^ z << 4) ^ (d ^ y);
        m += k[(p & 3) ^ e] ^ z;
        z = v[n] = (static_cast<int>(v[n] + m) & (0xBB390742 | 0x44C6F8BD));
    }

    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convertor;
    return convertor.to_bytes(l(v, false));
}