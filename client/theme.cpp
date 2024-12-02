#include "theme.h"

/*
Theme oceanBreezeDark(
    "#0D1B2A",  // Background: Dark Navy
    "#E0FBFC",  // Foreground: Light Cyan
    "#1B263B",  // Primary: Midnight Blue
    "#415A77",  // Light Background: Steel Blue
    "#778DA9",  // Secondary: Cool Gray
    "#E0FBFC"   // Light Foreground: Light Cyan
);

Theme oceanBreezeLight(
    "#E0FBFC",  // Background: Light Cyan
    "#1B263B",  // Foreground: Midnight Blue
    "#415A77",  // Primary: Steel Blue
    "#F5F9FA",  // Light Background: White Smoke
    "#A9C6D8",  // Secondary: Sky Blue
    "#415A77"   // Light Foreground: Steel Blue
);

Theme sunsetGlowDark(
    "#2F1B1B",  // Background: Dark Maroon
    "#FFDDD2",  // Foreground: Soft Pink
    "#9D0208",  // Primary: Crimson Red
    "#6A040F",  // Light Background: Deep Ruby
    "#D00000",  // Secondary: Fire Red
    "#FFDDD2"   // Light Foreground: Soft Pink
);

Theme sunsetGlowLight(
    "#FFDDD2",  // Background: Soft Pink
    "#6A040F",  // Foreground: Deep Ruby
    "#9D0208",  // Primary: Crimson Red
    "#FFD7C2",  // Light Background: Light Coral
    "#FF5733",  // Secondary: Bright Orange
    "#9D0208"   // Light Foreground: Crimson Red
);

Theme forestWhisperDark(
    "#1B2B1B",  // Background: Deep Green
    "#C7F9CC",  // Foreground: Mint Green
    "#40916C",  // Primary: Forest Green
    "#74C69D",  // Light Background: Soft Green
    "#95D5B2",  // Secondary: Light Green
    "#C7F9CC"   // Light Foreground: Mint Green
);

Theme forestWhisperLight(
    "#C7F9CC",  // Background: Mint Green
    "#1B2B1B",  // Foreground: Deep Green
    "#40916C",  // Primary: Forest Green
    "#D8F3DC",  // Light Background: Pale Green
    "#95D5B2",  // Secondary: Light Green
    "#40916C"   // Light Foreground: Forest Green
);

Theme midnightAuroraDark(
    "#1A1A2E",  // Background: Deep Midnight
    "#E94560",  // Foreground: Bright Coral
    "#16213E",  // Primary: Midnight Blue
    "#53354A",  // Light Background: Mulberry
    "#A7226E",  // Secondary: Magenta
    "#E94560"   // Light Foreground: Bright Coral
);

Theme midnightAuroraLight(
    "#F5F6FA",  // Background: Pale Gray
    "#16213E",  // Foreground: Midnight Blue
    "#53354A",  // Primary: Mulberry
    "#F7D9D9",  // Light Background: Soft Pink
    "#E94560",  // Secondary: Bright Coral
    "#53354A"   // Light Foreground: Mulberry
);




*/
Theme::Theme(QString background,QString foreground, QString primary, QString lightbackground, QString secondary, QString lightforeground){
    _background = background;
    _foreground = foreground;
    _primary = primary;
    _lightbackground = lightbackground;
    _secondary = background;
    _lightforeground = lightforeground;
}


QString Theme::getBackground() const
{
    return _background;
}

void Theme::setBackground(const QString &newBackground)
{
    _background = newBackground;
}

QString Theme::getForeground() const
{
    return _foreground;
}

void Theme::setForeground(const QString &newForeground)
{
    _foreground = newForeground;
}

QString Theme::getPrimary() const
{
    return _primary;
}

void Theme::setPrimary(const QString &newPrimary)
{
    _primary = newPrimary;
}

QString Theme::getLightbackground() const
{
    return _lightbackground;
}

void Theme::setLightbackground(const QString &newLightbackground)
{
    _lightbackground = newLightbackground;
}

QString Theme::getSecondary() const
{
    return _secondary;
}

void Theme::setSecondary(const QString &newSecondary)
{
    _secondary = newSecondary;
}

QString Theme::getLightforeground() const
{
    return _lightforeground;
}

void Theme::setLightforeground(const QString &newLightforeground)
{
    _lightforeground = newLightforeground;
}
