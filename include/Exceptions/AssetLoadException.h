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
    /*! One of the values in the assetdef.yaml file is in the incorrect
       format. */
    AssetDefInvalidFormat,
    /*! The file that the assetdef.yaml file points to doesn't exist. */
    SourceFileMissing,
    /*! Some other error occurred when loading the asset. */
    UnknownError
  };

  // Constructors/Destructors
  AssetLoadException(const AssetLoadExceptionReason reason)
      : _reason(reason),
        runtime_error(AssetLoadException::RuntimeErrorMessage) {}

  AssetLoadException(const AssetLoadExceptionReason reason, string extraData)
      : _reason(reason), _extraData(extraData),
        runtime_error(AssetLoadException::RuntimeErrorMessage) {}

  AssetLoadException(const exception *innerException)
      : _innerException(innerException),
        _reason(AssetLoadExceptionReason::UnknownError),
        runtime_error(AssetLoadException::RuntimeErrorMessage) {}

  ~AssetLoadException() {}

  // Methods
  virtual const char *what() const noexcept {
    const char *parentMessage = std::runtime_error::what();
    stringstream output;
    switch (_reason) {
    case AssetLoadExceptionReason::AssetDefMissing: {
      output << parentMessage << "The assetdef.yaml file is missing from the "
                                 "asset path specified. "
                                 "Path: " << _extraData << endl;
      break;
    }
    case AssetLoadExceptionReason::AssetDefMissingKey: {
      output << parentMessage
             << "The assetdef.yaml file has a missing manditory data key. Key: "
             << _extraData << endl;
      break;
    }
    case AssetLoadExceptionReason::AssetDefInvalidFormat: {
      output << parentMessage
             << "One of the values in the assetdef.yaml file is "
                "in the incorrect "
                "format. Key: " << _extraData << endl;
      break;
    }
    case AssetLoadExceptionReason::SourceFileMissing: {
      output << parentMessage
             << "The file that the assetdef.yaml file points to doesn't exist. "
                "Filename: " << _extraData << endl;
      break;
    }
    case AssetLoadExceptionReason::UnknownError: {
      string innerMessage = "Unknown";
      if (_innerException != nullptr) {
        innerMessage = _innerException->what();
      }
      output << parentMessage
             << "An unhandled error has occurred when loading the asset. Inner "
                "exception: " << innerMessage << endl;
      break;
    }
    default: {
      output << parentMessage
             << "The AssetLoadExceptionReason field is not set correctly. This "
                "should not happen." << endl;
      break;
    }
    }

    return output.str().c_str();
  }

private:
  // Fields
  AssetLoadExceptionReason _reason;
  const string _extraData = "";
  const exception *_innerException = nullptr;
};

#endif
