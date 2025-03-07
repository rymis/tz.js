/*
 * tzcpp - Library for working with timezones in C++
 *
 * Written in 2019 by Mikhail Ryzhov <rymiser@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to the
 * public domain worldwide.  This software is distributed without any
 * warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software.  If not, see
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
/* tzcpp @@VERSION@@; tzdata @@TZDATA_VERSION@@ */

/*
 * This library is based on tz.js public domain library
 */

#pragma once

#include <string>
#include <vector>
#include <ctime>

namespace tzcpp {

    struct ZoneInfo {
        int offset = 0;
        const char* abbr = nullptr;
        bool is_dst = false;

        bool empty() const {
            return abbr == nullptr;
        }
    };

    class TimeZone {
        size_t index_;
        TimeZone(size_t idx) : index_(idx) {
        }
    public:
        TimeZone();
        // Get rule by utc or pseudo local time:
        ZoneInfo rule(int64_t, bool pseudo_local = false);
        // Name of the rule:
        std::string rule_name() const;

        // Get rules from the array.
        size_t size() const;
        // Get nth rule from the array.
        ZoneInfo operator [] (size_t) const;

        // Search timezone in database. If not found empty timezone is returned.
        static TimeZone by_name(std::string);
    };

    // Get timezone class by name.
    inline TimeZone get_timezone(std::string name) {
        return TimeZone::by_name(name);
    }

    // Get timezone information from database. If not found returns empty timezone (abbr == nullptr).
    // If pseudo_local == true then function thinks about the time as about the local time converted
    // to seconds since apoch using GMT functions.
    // Current behaviour for ambiguous times is to return last applicable timezone.
    ZoneInfo get_zoneinfo(std::string, int64_t, bool pseudo_local = false) noexcept;

    // Get library version as git commit hash:
    const char* version() noexcept;
    // Get data version of tzinfo database:
    const char* data_version() noexcept;

    // Get list of all known timezones in database:
    std::vector<std::string> all_timezones();

    // Check if timezone is present in database (O(1) operation)
    bool has_timezone(std::string) noexcept;

    // Get all the timezone rules from the database.
    std::vector<std::pair<int64_t, ZoneInfo>> dump_timezone(std::string);

} // namespace tzcpp
