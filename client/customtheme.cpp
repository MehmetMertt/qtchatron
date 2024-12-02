#include "customtheme.h"

CustomTheme::CustomTheme() {
    // Initialize the container with all predefined themes
    themes = {
        {"Ocean Breeze", {Theme("#0D1B2A", "#E0FBFC", "#1B263B", "#415A77", "#778DA9", "#E0FBFC"),
                          Theme("#E0FBFC", "#1B263B", "#415A77", "#F5F9FA", "#A9C6D8", "#415A77")}},
        {"Sunset Glow",  {Theme("#2F1B1B", "#FFDDD2", "#9D0208", "#6A040F", "#D00000", "#FFDDD2"),
                         Theme("#FFDDD2", "#6A040F", "#9D0208", "#FFD7C2", "#FF5733", "#9D0208")}},
        {"Forest Whisper", {Theme("#1B2B1B", "#C7F9CC", "#40916C", "#74C69D", "#95D5B2", "#C7F9CC"),
                            Theme("#C7F9CC", "#1B2B1B", "#40916C", "#D8F3DC", "#95D5B2", "#40916C")}},
        {"Midnight Aurora", {Theme("#1A1A2E", "#E94560", "#16213E", "#53354A", "#A7226E", "#E94560"),
                             Theme("#F5F6FA", "#16213E", "#53354A", "#F7D9D9", "#E94560", "#53354A")}}
    };

    // Set a default theme (e.g., Ocean Breeze Dark)
    currentTheme = themes["Ocean Breeze"].dark;
}
