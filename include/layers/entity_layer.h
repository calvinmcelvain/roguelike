#ifndef ENTITY_LAYER_H
#define ENTITY_LAYER_H

#include <memory>
#include <vector>

#include "enemy.h"
#include "player.h"
#include "render_stack.h"

class EntityLayer : public RenderStack {
 public:
  /**
   * @brief Construct a new Entity Layer.
   *
   * NOTE: The reason we want to pass the player & enemies seperately is because
   * we want to render the player last. Such that if a player attacks an enemy
   * via melee, the player will render on top of the enemy.
   *
   * @param h Height of the layer window (in rows).
   * @param w Width of the layer window (in columns).
   * @param player The player entity to draw each frame.
   * @param enemies The enemy list to draw each frame.
   */
  EntityLayer(int h, int w, const Player& player,
              const std::vector<std::unique_ptr<Enemy>>& enemies);

  /**
   * @brief Draw enemy entities.
   *
   */
  void drawEnemies();

  /**
   * @brief Draw player entity.
   *
   */
  void drawPlayer();

  /**
   * @brief Draw all alive entities into the layer window.
   *
   */
  void doRender() override;

 private:
  const Player& player;
  const std::vector<std::unique_ptr<Enemy>>& enemies;
};

#endif