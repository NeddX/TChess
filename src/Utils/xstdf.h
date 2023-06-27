#ifndef TRC_UTILS_XSTDF_H
#define TRC_UTILS_XSTDF_H

#include <sdafx.h>

namespace trc::utils::string
{
    inline std::vector<std::string> Split(const std::string& str, char delimiter)
    {
		std::vector<std::string> tokens;
        std::istringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter))
            tokens.push_back(token);

        return tokens;
    }
}

#endif // TRC_UTILS_XSTDF_H
