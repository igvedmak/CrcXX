#include <boost/crc.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

namespace Utils {
    /**
    * @brief                                    This function converts any type to string.
    * 
    * @tparam T                                 Type of the parameter.
    * @param t                                  The parameter we want to convert to string.
    * @return constexpr std::string             Value in string format.
    */
    template<typename T>
    constexpr inline std::string Stringify(T const& t) {
        if constexpr (std::is_same_v<T, std::string>) {
            return t;
        } 
        return boost::lexical_cast<std::string>(t); 
    }

    /**
     * @brief                                   Helper for choosing const char* or unsigned char*.
     * 
     * @tparam T                                Type of the parameter.
     */
    template <typename T>
    using char_type = typename std::conditional_t<std::is_same_v<T, char>, unsigned char, T>;

    /**
     * @brief                                   Helper struct to get the appropriate CRC type for a given number of bits.
     * @tparam Bits                             The number of bits for the CRC algorithm (16/32).
     */
    template <int Bits>
    struct crc_type_helper;

    /**
     * @brief                                   Specialization of crc_type_helper for 32 bits, using boost::crc_32_type.
     */
    template<>
    struct crc_type_helper<16> {
        using type = boost::crc_16_type;
    };

    /**
     * @brief                                   Specialization of crc_type_helper for 32 bits, using boost::crc_32_type.
     */
    template<>
    struct crc_type_helper<32> {
        using type = boost::crc_32_type;
    };

    /**
     * @brief                                   Helper struct for result type determination.
     *
     * @tparam T                                Type of the result.
     * @tparam Bits                             The number of bits for the CRC algorithm (16/32).
     */
    template<typename T, int Bits>
    struct crc_result_type_helper {
        using type = T;
    };

    template<int Bits>
    struct crc_result_type_helper<std::string, Bits> {
        using type = std::string;
    };

    template<int Bits>
    struct crc_result_type_helper<unsigned int, Bits> {
        using type = unsigned int;
    };

    template<int Bits>
    struct crc_result_type_helper<unsigned short, Bits> {
        using type = unsigned short;
    };

    /**
     * @brief                                   This functions calculates CRC of a string and return as string/unsigned int.
     * @tparam T                                The return type of the function (std::string/unsigned int).
     * @tparam Bits                             The number of bits for the CRC algorithm (16/32).
     * @param buffer                            A pointer to the buffer to calculate the CRC from.
     * @param len                               The length of the buffer.
     * @return T                                The computed CRC checksum as the specified result type.
     *                                          If T is std::string, the result will be returned as a hex string.
     *                                          If T is unsigned int or unsigned short, the result will be returned as an integer.
     *                                          Otherwise, 0 will be returned.
     */
    template<typename T, int Bits = 32, typename U = const char*>
    typename crc_result_type_helper<T, Bits>::type crcXX(char_type<U> buffer, const size_t len) {
        /* Get the appropriate CRC type for the number of bits */
        typename crc_type_helper<Bits>::type crcType;
        crcType.process_bytes(buffer, len);
        if constexpr (std::is_same_v<T, std::string>) {
            return (boost::format("%0" + Stringify(Bits / 4) + "x") % crcType.checksum()).str();
        } else {
            return static_cast<typename crc_result_type_helper<T, Bits>::type>(crcType.checksum()); // Return CRC as an unsigned int/short
        }
    }

    /**
     * @brief                                   This functions calculates CRC of a string and return as string/unsigned int.
     * @tparam T                                The return type of the function (std::string/unsigned int).
     * @tparam Bits                             The number of bits for the CRC algorithm (16/32).
     * @param buffer                            A pointer to the buffer to calculate the CRC from.
     * @return T                                The computed CRC checksum as the specified result type.
     *                                          If T is std::string, the result will be returned as a hex string.
     *                                          If T is unsigned int or unsigned short, the result will be returned as an integer.
     *                                          Otherwise, 0 will be returned.
     */
    template<typename T, int Bits = 32>
    T crcXX(std::string const& buffer) {
        return crcXX<T, Bits>(buffer.data(), buffer.length());
    }
} // namespace Utils
