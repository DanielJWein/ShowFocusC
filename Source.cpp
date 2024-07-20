#define UNICODE 1
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

#define SFC_MIN_LENGTH 1
#define SFC_SLEEP_INTERVAL 50
#define SFC_ENABLE_LOCALE 0
#define SFC_BUFFERLENGTH 256

#include <iostream>

using namespace std;

#if SFC_ENABLE_LOCALE
#include <locale>

/// <summary>
/// Sets the locale to the specified locale
/// </summary>
/// <param name="newLocale">The locale code to set</param>
static void setNewLocale( const char *newLocale ) {
    try {
        locale::global( locale( newLocale ) );
        wcout.imbue( locale( newLocale ) );
    }
    catch ( ... ) {
        wprintf( L"Failed to set new locale." );
    }
}
#endif

int main( int argc, const char *argv[ ] ) {
    wchar_t s[ SFC_BUFFERLENGTH ] = { 0 };
    HWND h = 0, hPrev = 0;
    HWND thisHandle = GetConsoleWindow( );

#if SFC_ENABLE_LOCALE
    setNewLocale( argc > 1 ? argv[ 1 ] : setlocale( LC_ALL, NULL ) );

    SetConsoleOutputCP( CP_UTF8 );
    SetConsoleCP( CP_UTF8 );
#endif

    wprintf( L"ShowFocusC 1.0 by Daniel Wein.\n" );
    wprintf( L"Started August 31, 2018, Released July 20, 2024.\n" );
    wprintf( L"If you run into any trouble or are just curious, check help.txt.\n" );

    SetConsoleTitle( L"ShowFocusC" );
    SetWindowText( thisHandle, L"ShowFocusC" );

    while ( true ) {
        h = GetForegroundWindow( );
        if ( h != hPrev ) {
            memset( s, 0, SFC_BUFFERLENGTH * sizeof( wchar_t ) );
            GetWindowText( h, s, SFC_BUFFERLENGTH );
            if ( wcslen( s ) >= SFC_MIN_LENGTH )
                wprintf_s( L"%s\n", s );
            hPrev = h;
        }
        Sleep( SFC_SLEEP_INTERVAL ); //Update eight times a second.
    }
}
