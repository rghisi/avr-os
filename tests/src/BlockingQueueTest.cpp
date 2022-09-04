//
// Created by ghisi on 01.09.22.
//

#include <gtest/gtest.h>
#include "../../avr/src/BlockingQueue.h"
#include "../../avr/src/BlockingQueue.cpp"

class Dummy {
private:
public:
    Dummy() {
        this->someField = 0;
        this->someArray = new uint8_t[0];
        this->arraySize = 0;
    }
    Dummy(uint8_t someNumber, uint8_t* someArray, uint8_t arraySize) {
        this->someField = someNumber;
        this->arraySize = arraySize;
        this->someArray = someArray;
    }
    ~Dummy() {
        delete [] this->someArray;
    }

    uint8_t someField;
    uint8_t arraySize;
    uint8_t* someArray;
};

TEST(BlockingQueue, ShouldAcceptElementAndReturnTrue_WhenQueueHasSpaceAvailable) {
    uint8_t elementData[] = "abcde";
    auto* element = new Dummy(1, elementData, 6);

    auto* queue = new BlockingQueue<Dummy>(2);

    ASSERT_TRUE(queue->offer(element));
    ASSERT_TRUE(queue->offer(element));
}

TEST(BlockingQueue, ShouldNotAcceptElementAndReturnFalse_WhenQueueIsFull) {
    uint8_t elementOneData[] = "abcde";
    auto* elementOne = new Dummy(1, elementOneData, 6);
    uint8_t elementTwoData[] = "abcdefghijklmnopqrstuvxyz";
    auto* elementTwo = new Dummy(1, elementTwoData, 26);
    uint8_t elementThreeData[] = "xyz";
    auto* elementThree = new Dummy(1, elementThreeData, 4);

    auto* queue = new BlockingQueue<Dummy>(2);

    ASSERT_TRUE(queue->offer(elementOne));
    ASSERT_TRUE(queue->offer(elementTwo));
    ASSERT_FALSE(queue->offer(elementThree));
}

TEST(BlockingQueue, ShouldReturnNullptr_WhenEmpty) {
    auto* queue = new BlockingQueue<Dummy>(2);

    uint8_t elementOneData[] = "abcde";
    auto* elementOne = new Dummy(1, elementOneData, 6);
    uint8_t elementTwoData[] = "abcdefghijklmnopqrstuvxyz";
    auto* elementTwo = new Dummy(2, elementTwoData, 26);
    ASSERT_TRUE(queue->offer(elementOne));
    ASSERT_TRUE(queue->offer(elementTwo));

    Dummy* firstPolled = queue->poll();
    ASSERT_EQ(elementOne, firstPolled);

    Dummy* secondPolled = queue->poll();
    ASSERT_EQ(elementTwo, secondPolled);

    Dummy* thirdPolled = queue->poll();
    ASSERT_EQ(nullptr, thirdPolled);
}

TEST(BlockingQueue, ShouldReturnTheNextElement_WhenNotEmpty) {
    uint8_t elementOneData[] = "abcde";
    auto* elementOne = new Dummy(1, elementOneData, 6);
    uint8_t elementTwoData[] = "abcdefghijklmnopqrstuvxyz";
    auto* elementTwo = new Dummy(2, elementTwoData, 26);

    auto* queue = new BlockingQueue<Dummy>(2);

    ASSERT_TRUE(queue->offer(elementOne));
    ASSERT_TRUE(queue->offer(elementTwo));

    Dummy* firstPolled = queue->poll();
    ASSERT_EQ(elementOne, firstPolled);

    Dummy* secondPolled = queue->poll();
    ASSERT_EQ(elementTwo, secondPolled);

    Dummy* thirdPolled = queue->poll();
    ASSERT_EQ(nullptr, thirdPolled);
}

TEST(BlockingQueue, ShouldReturnAcceptAndReturnElements_WhenUsedExtensivelly) {
    uint8_t elementOneData[] = "abcde";
    auto* elementOne = new Dummy(1, elementOneData, 6);
    uint8_t elementTwoData[] = "abcdefghijklmnopqrstuvxyz";
    auto* elementTwo = new Dummy(2, elementTwoData, 26);
    uint8_t elementThreeData[] = "xyz";
    auto* elementThree = new Dummy(2, elementThreeData, 4);

    auto* queue = new BlockingQueue<Dummy>(2);

    ASSERT_TRUE(queue->offer(elementOne));
    ASSERT_TRUE(queue->offer(elementTwo));
    ASSERT_FALSE(queue->offer(elementThree));

    Dummy* firstPolled = queue->poll();
    ASSERT_EQ(elementOne, firstPolled);

    ASSERT_TRUE(queue->offer(elementThree));

    Dummy* secondPolled = queue->poll();
    ASSERT_EQ(elementTwo, secondPolled);

    Dummy* thirdPolled = queue->poll();
    ASSERT_EQ(elementThree, thirdPolled);
}

TEST(BlockingQueue, ShouldFreeResources_WhenQueueIsDeleted) {
    auto* queue = new BlockingQueue<Dummy>(2);

    delete queue;

    EXPECT_DEATH(queue->poll(), "");
}


TEST(BlockingQueue, ShouldBeEmpty_WhenQueueHasNoItems) {
    auto* queue = new BlockingQueue<Dummy>(2);

    ASSERT_TRUE(queue->isEmpty());
}

TEST(BlockingQueue, ShouldNotBeEmpty_WhenQueueHasAtLeastOneItem) {
    uint8_t elementData[] = "abcde";
    auto* element = new Dummy(1, elementData, 6);
    auto* queue = new BlockingQueue<Dummy>(2);

    queue->offer(element);

    ASSERT_FALSE(queue->isEmpty());
}

TEST(BlockingQueue, ShouldBeFull_WhenNoMoreElementsAreAccepted) {
    uint8_t elementData[] = "abcde";
    auto* element = new Dummy(1, elementData, 6);
    auto* queue = new BlockingQueue<Dummy>(2);

    ASSERT_FALSE(queue->isFull());
    queue->offer(element);
    ASSERT_FALSE(queue->isFull());
    queue->offer(element);
    ASSERT_TRUE(queue->isFull());
}