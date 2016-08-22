/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef V4L2_CAMERA_HAL_METADATA_SLIDER_CONTROL_OPTIONS_H_
#define V4L2_CAMERA_HAL_METADATA_SLIDER_CONTROL_OPTIONS_H_

#include <errno.h>

#include <vector>

#include "../common.h"
#include "control_options_interface.h"

namespace v4l2_camera_hal {

// SliderControlOptions offer a range of acceptable values, inclusive.
template <typename T>
class SliderControlOptions : public ControlOptionsInterface<T> {
 public:
  // |min| must be <= |max|.
  SliderControlOptions(T min, T max) : min_(min), max_(max) {}

  virtual std::vector<T> MetadataRepresentation() override {
    return {min_, max_};
  };
  virtual bool IsSupported(const T& option) override {
    return option >= min_ && option <= max_;
  };
  virtual int DefaultValueForTemplate(int template_type,
                                      T* default_value) override {
    // TODO(b/31017806): More complex logic, depend on template_type.
    if (min_ > max_) {
      HAL_LOGE("No valid default slider option, min is greater than max.");
      return -ENODEV;
    }
    // Default to the min value.
    *default_value = min_;
    return 0;
  }

 private:
  T min_;
  T max_;
};

}  // namespace v4l2_camera_hal

#endif  // V4L2_CAMERA_HAL_METADATA_SLIDER_CONTROL_OPTIONS_H_
