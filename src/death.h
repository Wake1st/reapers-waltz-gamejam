#ifndef DEATH
#define DEATH

#include <unordered_map>

typedef enum DeathTypes
{
  CRUSHED,
  SPIKED,
  CAUGHT,
} DeathTypes;

class Death
{
public:
  static void add(DeathTypes deathType);
  static bool allDead();

private:
  static std::unordered_map<DeathTypes, bool> deaths;
};

std::unordered_map<DeathTypes, bool> Death::deaths = {
    {DeathTypes::CRUSHED, false},
    {DeathTypes::SPIKED, false},
    {DeathTypes::CAUGHT, false},
};

void Death::add(DeathTypes deathType)
{
  deaths[deathType] = true;
}

bool Death::allDead()
{
  return (
      (deaths[DeathTypes::CRUSHED]) &&
      (deaths[DeathTypes::SPIKED]) &&
      (deaths[DeathTypes::CAUGHT]));
}

#endif
