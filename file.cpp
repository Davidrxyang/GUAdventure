#include "file.h"

GameFile::GameFile()
{
    player_name = "";
    player_type = 0;
    player_mode = normal;
    current_level = 1;
    current_score = 0;
    remaining_enemies = 0;
    health = 0;
    bool is_empty = true;
} // default constructor

void GameFile::read(string file_path)
{
    if (empty(file_path))
    {
        cout << "Failed to read file: Empty File." << endl;
    } // if - empty
    else
    {
        ifstream in_file;
        in_file.open(file_path.c_str());

        if (!in_file)
        {
            cout << "Failed to open file: check file name and path." << endl;
        } // if - failed to open file

        // READING FILE
        char delim = '_';

        player_name = read_string(in_file);

        in_file >> delim >> player_type >> delim >> current_level >> delim >> current_score >> delim >> 
        remaining_enemies >> delim >> health >> delim >> x >> delim >> y;
    
        switch (player_type)
        {
            case 0:
            player_mode = normal;
            break;

            case 1:
            player_mode = melee;
            break;

            case 2:
            player_mode = projectile;
            break;

            case 3:
            player_mode = hybrid;
            break;

            case 4:
            player_mode = admin;
            break;
        } // switch - player mode conversion

        in_file.close();
    } // else - file open success
} // GameFile::read

void GameFile::write(string file_path, string p_name, int p_type, size_t c_level, size_t c_score, size_t r_enemies, size_t health, double x, double y)
{
    is_empty = false;
    fstream out_file;
    out_file.open(file_path.c_str(), ios::out);
    char delim = '_';

    out_file << '\"' << p_name << '\"' << delim << p_type << delim << c_level << delim << c_score << delim << 
    r_enemies << delim << health << delim << x << delim << y;

    out_file.close();
} // GameFile::write

void GameFile::write(string file_path)
{
    ofstream out_file(file_path.c_str());
    out_file.close();
    // creates a file, for use in constructor
} // GameFile::write

bool GameFile::empty(string file_path)
{
    ifstream in_file;
    in_file.open(file_path.c_str());
    string p = "";
    in_file >> p;

    if (p == "")
    {
        return true;
    } // if - empty true
    else
    {
        return false;
    } // else
} // GameFile::empty

string GameFile::read_string (istream &in_file) const
{
    string s;
    char ch;
    char delim = '\"';

    in_file >> ch;

    getline(in_file, s, delim);

    return s;
} // File::read_string