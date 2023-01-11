#ifndef SIGNAL_H
#define SIGNAL_H

#include <map>
#include <sstream>
#include <string>
#include <vector>

using Signals = std::vector<std::string>;

struct Parser {
    /**
     * @brief Parses signal patterns from string and returns each of them into a
     * vector
     *
     */
    static Signals parse_signal_patterns(std::string signal);

    /**
     * @brief Parses output values from string and returns each of them into a
     * vector.
     *
     */
    static Signals parse_output_values(std::string signal);
};

struct Decoder {
    /**
     * @brief Decodes list of patterns to a map of what number on the segment
     * each string represents.
     *
     * @param patterns A list of signal patterns to decode.
     */
    static std::map<std::string, int> decode(Signals patterns);

    /**
     * @brief Returns if the signal given is one of the unique digits: 1, 4,
     * 7, 8.
     *
     */
    static int convert_to_unique_digit(const std::string &signal);

    /**
     * @brief Converts the segment configuration into a map of key-value pairs
     * of signal and number it represents.
     *
     * @param config
     * @return std::map<std::string, int>
     */
    static std::map<std::string, int>
    convert_config_to_map(std::vector<std::string> config);
};

#endif