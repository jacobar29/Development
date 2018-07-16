/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== chords.txt ==================
static const unsigned char temp_binary_data_0[] =
"A 2 1 0 0\r\n"
"A# 3 2 1 1\r\n"
"A7 0 1 0 0\r\n"
"A#7 1 2 1 1\r\n"
"Am 2 0 0 0 \r\n"
"A#m 3 1 1 1\r\n"
"Am7 0 4 3 3\r\n"
"A#m7 1 1 1 1\r\n"
"B 4 3 2 2\r\n"
"B7 2 3 2 2\r\n"
"Bm 4 2 2 2\r\n"
"Bm7 2 2 2 2\r\n"
"C 0 0 0 3\r\n"
"C# 1 1 1 4\r\n"
"C7 0 0 0 1\r\n"
"C#7 1 1 1 2\r\n"
"Cm 0 3 3 3\r\n"
"C#m 1 1 0, 0\r\n"
"Cm7 3 3 3 3\r\n"
"C#m7 1 1 0 2\r\n"
"D 2 2 2 4\r\n"
"D# 3 3 3 1\r\n"
"D7 2 2 2 3\r\n"
"D#7 3 3 3 4\r\n"
"Dm 2 2 1 0\r\n"
"D#m 3 3 2 1\r\n"
"Dm7 2 2 1 3\r\n"
"D#m7 3 3 2 1\r\n"
"E 4 4 4 2\r\n"
"E# 4 4 4 2\r\n"
"E7 1 2 0 2\r\n"
"Em 0 3 2 1\r\n"
"Em7 0 2 0 2\r\n"
"F 2 0 1 0\r\n"
"F# 3 1 2 1\r\n"
"F7 2 3 1 0\r\n"
"F#7 3 4 2 4\r\n"
"Fm 1 0 1 2\r\n"
"F#m 2 1 2 0\r\n"
"Fm7 1 2 1 2\r\n"
"F#m7 2 4 2 4\r\n"
"G 0 2 3 2\r\n"
"G# 5 3 4 3\r\n"
"G7 0 2 1 2\r\n"
"G#7 1 3 2 3\r\n"
"Gm 0 2 3 1\r\n"
"G#m 4 3 4 2\r\n"
"Gm7 0 2 1 1\r\n"
"G#m7 1 3 2 2\r\n";

const char* chords_txt = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0xfe82cdc8:  numBytes = 610; return chords_txt;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "chords_txt"
};

const char* originalFilenames[] =
{
    "chords.txt"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
