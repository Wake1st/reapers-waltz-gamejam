// #ifndef TEST_TRIGGERS
// #define TEST_TRIGGERS

// #include <map>

// #include "trigger.h"
// #include "input.h"
// #include "actor.h"

// typedef struct TestTriggersResources
// {
//   Texture2D texture;
// } TestTriggersResources;

// class TestTriggers
// {
// public:
//   TestTriggers(TestTriggersResources res)
//   {
//     input = new InputHandler();
//     actor = new Actor(res.texture, 12 + 12 * MAP_WIDTH);

//     triggers = {
//         {4 + 4 * MAP_WIDTH, new Trigger(4 + 4 * MAP_WIDTH)},
//         {5 + 4 * MAP_WIDTH, new Trigger(5 + 4 * MAP_WIDTH)},
//         {9 + 7 * MAP_WIDTH, new Trigger(9 + 7 * MAP_WIDTH)},
//     };
//   }
//   void update();
//   void draw();

// private:
//   std::map<int, Trigger *> triggers;
//   InputHandler *input;
//   Actor *actor;
// };

// void TestTriggers::update()
// {
//   Command command = input->handleInput();
//   if (command)
//   {
//     actor->move(&command);
//   }

//   // check for triggers
//   for (const auto &[cell, trigger] : triggers)
//   {
//     trigger->activate(actor->currentCell == cell);
//   }

//   actor->update();
// }

// void TestTriggers::draw()
// {
//   actor->draw();

//   for (const auto &pair : triggers)
//   {
//     pair.second->draw();

//     if (pair.second->active)
//     {
//       DrawText("TRIGGER ACTIVED", 20, 200, 20, WHITE);
//     }
//   }
// }

// #endif
