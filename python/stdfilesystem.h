/** \file
 * Fallback header for std::fileystem because gcc <= 8 still only has
 * experimental support.
 *
 * Use "filesystem" namespace instead of "std::filesystem". If your compiler
 * only has experimental support define "EXPERIMENTAL_FILESYSTEM" for the
 * preprocessor.
 */
#ifndef __STDFILESYSTEM_H__
#define __STDFILESYSTEM_H__


#ifdef EXPERIMENTAL_FILESYSTEM
    #include <experimental/filesystem>
    namespace filesystem = std::experimental::filesystem;
#else
    #include <filesystem>
    namespace filesystem = std::filesystem;
#endif


#endif
