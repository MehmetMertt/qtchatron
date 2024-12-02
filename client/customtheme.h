#include <map>
#include <string>
#include "theme.h"

// Struct to represent a pair of dark and light themes
struct ThemePair {
    Theme dark;
    Theme light;
};


/*example usage:
 *
CustomTheme customTheme;

Theme oceanBreezeDark = customTheme.getThemes()["Ocean Breeze"].dark;

customTheme.setCurrentTheme("Sunset Glow", false);

Theme current = customTheme.getCurrentTheme();

*/

class CustomTheme {
private:
    Theme currentTheme;
    std::map<std::string, ThemePair> themes;  // Key: Theme name, Value: ThemePair (dark and light)

public:
    CustomTheme();

    Theme getCurrentTheme() const {
        return currentTheme;
    }

    void setCurrentTheme(const std::string &themeName, bool darkMode) {
        if (themes.find(themeName) != themes.end()) {
            currentTheme = darkMode ? themes[themeName].dark : themes[themeName].light;
        }
    }

    std::map<std::string, ThemePair> getThemes() const {
        return themes;
    }
};
