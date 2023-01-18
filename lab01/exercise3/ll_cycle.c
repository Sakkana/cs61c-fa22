#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "ll_cycle.h"


int ll_has_cycle(node *head) {
    int turn = 1;
    node *fast = head;
    node *slow = head;
    while (fast != NULL && fast->next != NULLi) {
        assert(fast);
        if (turn == 1) {
            if (fast->next) {
                fast = fast->next;
            }

            assert(fast);

            if (fast->next) {
                fast = fast->next;
            }

            assert(fast);

            //printf("fast in %d\n", fast->value);

        } else {
            slow = slow->next;

            assert(slow);

            //printf("slow in %d\n", slow->value);
        }

        turn = 1 - turn;

        if (fast == slow) {
            return 1;
        }
    }

    return 0;
}
