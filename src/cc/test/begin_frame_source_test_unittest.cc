// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cc/test/begin_frame_source_test.h"

#include "cc/test/begin_frame_args_test.h"
#include "cc/test/mock_helper.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace cc {
namespace {
TEST(MockBeginFrameObserverTest, FailOnMissingCalls) {
  EXPECT_MOCK_FAILURE({
    ::testing::NiceMock<MockBeginFrameObserver> obs;
    EXPECT_BEGIN_FRAME_USED(obs, 100, 200, 300);
    EXPECT_BEGIN_FRAME_USED(obs, 400, 600, 300);

    obs.OnBeginFrame(
        CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 400, 600, 300));
  });
}

TEST(MockBeginFrameObserverTest, FailOnMultipleCalls) {
  EXPECT_MOCK_FAILURE({
    ::testing::NiceMock<MockBeginFrameObserver> obs;
    EXPECT_BEGIN_FRAME_USED(obs, 100, 200, 300);
    EXPECT_BEGIN_FRAME_USED(obs, 400, 600, 300);

    obs.OnBeginFrame(
        CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));
    obs.OnBeginFrame(
        CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));
    obs.OnBeginFrame(
        CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 400, 600, 300));
  });
}

TEST(MockBeginFrameObserverTest, FailOnWrongCallOrder) {
  EXPECT_MOCK_FAILURE({
    ::testing::NiceMock<MockBeginFrameObserver> obs;
    EXPECT_BEGIN_FRAME_USED(obs, 100, 200, 300);
    EXPECT_BEGIN_FRAME_USED(obs, 400, 600, 300);

    obs.OnBeginFrame(
        CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 400, 600, 300));
    obs.OnBeginFrame(
        CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));
  });
}

TEST(MockBeginFrameObserverTest, ExpectOnBeginFrame) {
  ::testing::NiceMock<MockBeginFrameObserver> obs;
  EXPECT_BEGIN_FRAME_USED(obs, 100, 200, 300);
  EXPECT_BEGIN_FRAME_USED(obs, 400, 600, 300);
  EXPECT_BEGIN_FRAME_USED(obs, 700, 900, 300);

  EXPECT_EQ(obs.LastUsedBeginFrameArgs(),
            MockBeginFrameObserver::kDefaultBeginFrameArgs);

  obs.OnBeginFrame(CreateBeginFrameArgsForTesting(
      BEGINFRAME_FROM_HERE, 100, 200,
      300));  // One call to LastUsedBeginFrameArgs
  EXPECT_EQ(
      obs.LastUsedBeginFrameArgs(),
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));

  obs.OnBeginFrame(CreateBeginFrameArgsForTesting(
      BEGINFRAME_FROM_HERE, 400, 600,
      300));  // Multiple calls to LastUsedBeginFrameArgs
  EXPECT_EQ(
      obs.LastUsedBeginFrameArgs(),
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 400, 600, 300));
  EXPECT_EQ(
      obs.LastUsedBeginFrameArgs(),
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 400, 600, 300));

  obs.OnBeginFrame(CreateBeginFrameArgsForTesting(
      BEGINFRAME_FROM_HERE, 700, 900,
      300));  // No calls to LastUsedBeginFrameArgs
}

TEST(MockBeginFrameObserverTest, ExpectOnBeginFrameStatus) {
  ::testing::NiceMock<MockBeginFrameObserver> obs;
  EXPECT_BEGIN_FRAME_USED(obs, 100, 200, 300);
  EXPECT_BEGIN_FRAME_DROP(obs, 400, 600, 300);
  EXPECT_BEGIN_FRAME_DROP(obs, 450, 650, 300);
  EXPECT_BEGIN_FRAME_USED(obs, 700, 900, 300);

  EXPECT_EQ(obs.LastUsedBeginFrameArgs(),
            MockBeginFrameObserver::kDefaultBeginFrameArgs);

  // Used
  obs.OnBeginFrame(
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));
  EXPECT_EQ(
      obs.LastUsedBeginFrameArgs(),
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));

  // Dropped
  obs.OnBeginFrame(
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 400, 600, 300));
  EXPECT_EQ(
      obs.LastUsedBeginFrameArgs(),
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));

  // Dropped
  obs.OnBeginFrame(
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 450, 650, 300));
  EXPECT_EQ(
      obs.LastUsedBeginFrameArgs(),
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 100, 200, 300));

  // Used
  obs.OnBeginFrame(
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 700, 900, 300));
  EXPECT_EQ(
      obs.LastUsedBeginFrameArgs(),
      CreateBeginFrameArgsForTesting(BEGINFRAME_FROM_HERE, 700, 900, 300));
}

}  // namespace
}  // namespace cc
