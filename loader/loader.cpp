#include <string_view>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

fs::path binkw32_path          { "binkw32.dll"          };
fs::path binkw32_bak_path      { "binkw32.dll.bak"      };
fs::path binkw32_patch_path    { "binkw32_patch.dll"    };
fs::path binkw32_original_path { "binkw32.original.dll" };

int install() {
    if ( !(fs::exists(binkw32_path)) ) {
        std::cerr << "Failed to find 'binkw32.dll'. Make sure you are in the right Hitman Bloodmoney directory.\n";
        return 1;
    }

    // Backup and original copy just in case u retards fuck it all the way up.
    if ( !(fs::exists(binkw32_bak_path)) ) {
        std::cout << "'binkw32.dll.bak' not found. Copying binkw32.dll to '" << binkw32_bak_path << "' and '" << binkw32_original_path << "'\n", 

        fs::copy_file(binkw32_path, binkw32_bak_path);
        fs::copy_file(binkw32_path, binkw32_original_path);
    } 

    if ( !(fs::exists(binkw32_patch_path)) ) {
        std::cerr << "Failed to find 'bink_patch.dll'.\n";
        return 1;
    }
    std::cout << "Copying 'bink_patch.dll' to '" << binkw32_bak_path << "' and '" << binkw32_original_path << "'\n", 
    fs::copy_file(binkw32_patch_path, binkw32_path, fs::copy_options::overwrite_existing);

    return 0;
}

int uninstall() {
    if ( !(fs::exists(binkw32_bak_path)) ) {
        std::cerr << "Refusing to delete 'binkw32.dll'... 'binkw32.dll.bak' not found.\n";
        return 1;
    }
    std::cout << "Reverting 'binkw32.dll' to original code. (overwriting binkw32.dll with binkw32.dll.bak)\n";
    fs::copy(binkw32_bak_path, binkw32_path, fs::copy_options::overwrite_existing);

    if ( (fs::exists(binkw32_original_path) ) ) {
        fs::remove(binkw32_original_path);
    }

    if ( (fs::exists(binkw32_patch_path) ) ) {
        fs::remove(binkw32_patch_path);
    }

    return 0;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        return install();
    } else if ( (argc == 2) && (std::string_view(argv[1]).compare("--uninstall") == 0) ) {
        return uninstall();
    } else {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << "[ --uninstall ]\n\n";
    }

    return 0;
}
