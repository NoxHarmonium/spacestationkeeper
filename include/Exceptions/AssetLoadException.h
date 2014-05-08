//
//  AssetLoadException.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 3/05/2014.
//
//

#ifndef SpaceStationKeeper_AssetLoadException_h
#define SpaceStationKeeper_AssetLoadException_h

#include <stdexcept>
#include <iostream>

using namespace std;

class AssetLoadException : public runtime_error {
public:
  // String Constants
  static constexpr const char *RuntimeErrorMessage =
      "There was an error loading an asset: ";

  // Enums
  /*! Defines the reason for the error when loading an asset. */
  enum class AssetLoadExceptionReason {
    /*! The assetdef.yaml file is missing from the asset path specified.*/
    AssetDefMissing,
    /*! The assetdef.yaml file has a missing manditory data key. */
    AssetDefMissingKey,
    /*! The YAML file could not be parsed by the YAML parser. */
    YamlParseError,
    /*! One of the values in the assetdef.yaml file is in the incorrect
       format. */
    AssetDefInvalidFormat,
    /*! Something that the asset needs to function is missing . */
    AssetDefMissingDependencies,
    /*! The file that the assetdef.yaml file points to doesn't exist. */
    SourceFileMissing,
    /*! The asset type is not supported in this version of the application. */
    UnsupportedAssetType,
    /*! The path provided is not valid. */
    InvalidPath,
    /*! Some other error occurred when loading the asset. */
    UnknownError
  };

  // Constructors/Destructors
  AssetLoadException(const AssetLoadExceptionReason reason)
      : _reason(reason),
        runtime_error(AssetLoadException::RuntimeErrorMessage) {
    generateMessage();
  }

  AssetLoadException(const AssetLoadExceptionReason reason, string extraData)
      : _reason(reason), _extraData(extraData),
        runtime_error(AssetLoadException::RuntimeErrorMessage) {
    generateMessage();
  }

  AssetLoadException(const exception *innerException)
      : _innerException(innerException),
        _reason(AssetLoadExceptionReason::UnknownError),
        runtime_error(AssetLoadException::RuntimeErrorMessage) {
    generateMessage();
  }

  ~AssetLoadException() {
    if (_exceptionMessage != nullptr) {
      delete[] _exceptionMessage;
    }
  }

  // Methods
  virtual const char *what() const noexcept { return _exceptionMessage; }

private:
  // Methods
  void generateMessage() {
    if (_exceptionMessage == nullptr) {
      const char *parentMessage = std::runtime_error::what();
      stringstream output;
      switch (_reason) {
      case AssetLoadExceptionReason::AssetDefMissing: {
        output << parentMessage << "The assetdef.yaml file is missing from the "
                                   "asset path specified. "
                                   "Path: " << _extraData;
        break;
      }
      case AssetLoadExceptionReason::AssetDefMissingKey: {
        output
            << parentMessage
            << "The assetdef.yaml file has a missing manditory data key. Key: "
            << _extraData;
        break;
      }
      case AssetLoadExceptionReason::YamlParseError: {
        output
            << parentMessage
            << "The YAML file could not be parsed by the YAML parser. Error: "
            << _extraData;
        break;
      }
      case AssetLoadExceptionReason::AssetDefInvalidFormat: {
        output << parentMessage
               << "One of the values in the assetdef.yaml file is "
                  "in the incorrect "
                  "format. Key: " << _extraData;
        break;
      }
      case AssetLoadExceptionReason::AssetDefMissingDependencies: {
        output << parentMessage
               << "Something that is needed for this asset is missing. Detail: "
               << _extraData;

        break;
      }
      case AssetLoadExceptionReason::SourceFileMissing: {
        output
            << parentMessage
            << "The file that the assetdef.yaml file points to doesn't exist. "
               "Filename: " << _extraData;
        break;
      }
      case AssetLoadExceptionReason::UnsupportedAssetType: {
        output << parentMessage << "The asset type is not supported in this "
                                   "version of the application. ";
        break;
      }
      case AssetLoadExceptionReason::InvalidPath: {
        output << parentMessage << "The provided path does not exist or is not "
                                   "a directory containing assets.";
        break;
      }
      case AssetLoadExceptionReason::UnknownError: {
        string innerMessage = "Unknown";
        if (_innerException != nullptr) {
          innerMessage = _innerException->what();
        }
        output
            << parentMessage
            << "An unhandled error has occurred when loading the asset. Inner "
               "exception: " << innerMessage;
        break;
      }
      default: {
        output
            << parentMessage
            << "The AssetLoadExceptionReason field is not set correctly. This "
               "should not happen.";
        break;
      }
      }

      // Text is in temporary memory, need to persist it for life of exception
      // object
      string s = output.str();
      _exceptionMessage = new char[s.length() + 1];
      strcpy(_exceptionMessage, s.c_str());
    }
  }

  // Fields
  AssetLoadExceptionReason _reason;
  const string _extraData = "";
  const exception *_innerException = nullptr;
  char *_exceptionMessage = nullptr;
};

#endif
