#pragma once

#include <c10/core/Allocator.h>
#include <ATen/core/ATenGeneral.h>
#include <ATen/Context.h>
#include <ATen/Device.h>
#include <ATen/DeviceGuard.h>
#include <ATen/DimVector.h>
#include <ATen/Dispatch.h>
#include <ATen/Formatting.h>
#include <ATen/Functions.h>
#ifdef NAMEDTENSOR_ENABLED
#include <ATen/NamedTensor.h>
#endif
#include <ATen/ScalarOps.h>
#include <ATen/Tensor.h>
#include <ATen/TensorGeometry.h>
#include <ATen/TensorOperators.h>
#include <ATen/Version.h>
#include <ATen/core/ATenGeneral.h>
#include <ATen/core/Generator.h>
#include <c10/core/Layout.h>
#include <ATen/core/Scalar.h>
#include <c10/core/Storage.h>
#include <ATen/TensorOptions.h>
#include <c10/util/Exception.h>
#include <ATen/core/ATenDispatch.h>
#include <ATen/core/UnsafeFromTH.h>
