SET(PREFIX_ext_openssl "${EXTPREFIX}" )

if (WIN32)
    if (MSVC)
    # Use the binaries from ConanCenter
        ExternalProject_Add(ext_openssl
            DOWNLOAD_DIR ${EXTERNALS_DOWNLOAD_DIR}
            URL https://files.kde.org/krita/build/dependencies/openssl-1.1.1k-win64-msvc.tgz
            URL_HASH SHA256=beae4c78e2f2b64cc3621402a34550ef1fffd08cd35b6a6802f22ed0460ff1d4

            BUILD_COMMAND ${CMAKE_COMMAND} -E echo Deploying openssl 64-bit dependencies
            CONFIGURE_COMMAND ""
            INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/include ${PREFIX_ext_openssl}/include
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/lib/libcrypto.lib ${PREFIX_ext_openssl}/lib
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/lib/libssl.lib ${PREFIX_ext_openssl}/lib
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/bin/libcrypto-1_1-x64.dll ${PREFIX_ext_openssl}/bin
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/bin/libssl-1_1-x64.dll ${PREFIX_ext_openssl}/bin
            UPDATE_COMMAND ""
        )
    else(MSVC)
    # Use the binaries from curl for Windows (https://github.com/curl/curl-for-win).
        ExternalProject_Add(ext_openssl
            DOWNLOAD_DIR ${EXTERNALS_DOWNLOAD_DIR}
            URL https://files.kde.org/krita/build/dependencies/openssl-1.1.1l_4-win64-mingw.zip
            URL_HASH SHA256=6582432d4f537323bfa032a1d91b4eee12efdf0c72e4fabdacc0ac5dd1685e9a

            BUILD_COMMAND ${CMAKE_COMMAND} -E echo Deploying openssl 64-bit dependencies
            CONFIGURE_COMMAND ""
            INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/include ${PREFIX_ext_openssl}/include
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/lib/libcrypto.dll.a ${PREFIX_ext_openssl}/lib
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/lib/libssl.dll.a ${PREFIX_ext_openssl}/lib
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/libcrypto-1_1-x64.dll ${PREFIX_ext_openssl}/bin
                    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/libssl-1_1-x64.dll ${PREFIX_ext_openssl}/bin
            UPDATE_COMMAND ""
        )
    endif(MSVC)
elseif (ANDROID)
    ExternalProject_Add( ext_openssl
        DOWNLOAD_DIR ${EXTERNALS_DOWNLOAD_DIR}
        URL https://www.openssl.org/source/openssl-1.1.1m.tar.gz
        URL_HASH SHA256=f89199be8b23ca45fc7cb9f1d8d3ee67312318286ad030f5316aca6462db6c96

        CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env
            ANDROID_NDK_HOME=${CMAKE_ANDROID_NDK}
            ANDROID_NDK=${CMAKE_ANDROID_NDK}
            PATH=${ANDROID_TOOLCHAIN_ROOT}/bin/:$ENV{PATH}
            <SOURCE_DIR>/Configure android-${CMAKE_ANDROID_ARCH} -D__ANDROID_API__=${ANDROID_PLATFORM_LEVEL}
            --prefix=${PREFIX_ext_openssl} --openssldir=ssl

        BUILD_COMMAND ${CMAKE_COMMAND} -E env
            PATH=${ANDROID_TOOLCHAIN_ROOT}/bin:$ENV{PATH}
            CXXFLAGS=-D__ANDROID_API__=${ANDROID_PLATFORM_LEVEL}
            make build_libs SHLIB_VERSION_NUMBER= SHLIB_EXT=_1_1.so
        INSTALL_COMMAND ${CMAKE_COMMAND} -E env
            PATH=${ANDROID_TOOLCHAIN_ROOT}/bin:$ENV{PATH}
            CXXFLAGS=-D__ANDROID_API__=${ANDROID_PLATFORM_LEVEL}
            make install_sw SHLIB_VERSION_NUMBER= SHLIB_EXT=_1_1.so

        INSTALL_DIR ${PREFIX_ext_openssl}

        UPDATE_COMMAND ""
)
else (WIN32)
    
    kis_ExternalProject_Add_with_separate_builds_apple(
        ext_openssl

        DOWNLOAD_DIR ${EXTERNALS_DOWNLOAD_DIR}
        URL https://www.openssl.org/source/openssl-1.1.1m.tar.gz
        URL_HASH SHA256=f89199be8b23ca45fc7cb9f1d8d3ee67312318286ad030f5316aca6462db6c96

        WORKING_DIRECTORY <SOURCE_DIR>
        CONFIGURE_COMMAND <SOURCE_DIR>/config --prefix=${PREFIX_ext_openssl} --openssldir=ssl
        
        BUILD_COMMAND make clean COMMAND make -j${SUBMAKE_JOBS} depend COMMAND make -j${SUBMAKE_JOBS}
        INSTALL_COMMAND make install
        
        INSTALL_DIR ${PREFIX_ext_openssl}

        UPDATE_COMMAND ""
    )

endif (WIN32)
