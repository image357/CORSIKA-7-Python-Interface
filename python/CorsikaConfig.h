#ifndef __CORSIKACONFIG_H__
#define __CORSIKACONFIG_H__

#include <string>


/** Stores CORSIKA config options received by the COAST interface.
 *
 * Defines an internal CorsikaConfig::CorsikaOption enumeration type in order
 * to handle unset or unknown CORSIKA config options.
 */
class CorsikaConfig {

    // interface types
    /** Internal enumeration type to handle unset or unknown CORSIKA options. */
    public:
        enum class CorsikaOption {
            FALSE,  /**< Used to indicate an unset option. */
            TRUE,   /**< Used to indicate a used option. */
            UNKNOWN /**< Used to indicate missing knowledge about an option. */
        };


    // members
    private:
        std::string mFilename;
        CorsikaOption mThinning;
        CorsikaOption mCurved;
        CorsikaOption mSlant;
        CorsikaOption mStackinput;
        CorsikaOption mPreshower;


    // public functions
    public:
        /** Default constructor sets everything to CorsikaOption::UNKNOWN and
         *  an empty std::string() for filename. */
        CorsikaConfig();

        /** Constructor that excatly accepts the parameters of the COAST
         *  interface.
         *
         *  During construction all whitespaces at the end of filename will be
         *  trimmed. Bools are converted to CorsikaConfig::CorsikaOption types.
         *
         *  @param filename Null terminated string that points to the CORSIKA
         *  binary file. May contain whitespaces.
         *  @param strlen Length of filename.
         *  @param thinning Indicates if THIN is used.
         *  @param curved Indicates if CURVED is used.
         *  @param slant Indicates if SLANT is used.
         *  @param stackinput Indicates if STACKIN is used.
         *  @param preshower Indicates if PRESHOWER is used.
         */
        CorsikaConfig(const char * filename, const int strlen,
                      const bool thinning, const bool curved, const bool slant,
                      const bool stackinput, const bool preshower);

        /** Set filename of the CORSIKA binary output file.
         *
         * Removes all whitespaces at the end of the filename.
         */
        void setFilename(const char * filename);

        /** Set filename of the CORSIKA binary output file.
         *
         * Removes all whitespaces at the end of the filename.
         */
        void setFilename(const char * filename, const int strlen);

        /** Indicate the usage of the CORSIKA config for the THIN option. */
        void setThinning(const bool val);

        /** Indicate the usage of the CORSIKA config for the CURVED option. */
        void setCurved(const bool val);

        /** Indicate the usage of the CORSIKA config for the SLANT option. */
        void setSlant(const bool val);

        /** Indicate the usage of the CORSIKA config for the STACKIN option. */
        void setStackinput(const bool val);

        /** Indicate the usage of the CORSIKA config for the PRESHOWER option */
        void setPreshower(const bool val);

        /** Get CORSIKA binary output filename. */
        std::string getFilename() const;

        /** Get CORSIKA config for the THIN option. */
        CorsikaOption getThinning() const;

        /** Get CORSIKA config for the CURVED option. */
        CorsikaOption getCurved() const;

        /** Get CORSIKA config for the SLANT option. */
        CorsikaOption getSlant() const;

        /** Get CORSIKA config for the STACKIN option. */
        CorsikaOption getStackinput() const;

        /** Get CORSIKA config for the PRESHOWER option. */
        CorsikaOption getPreshower() const;


    // private functions
    private:
        CorsikaOption boolToCorsikaOption(const bool val) const;

};


#endif
