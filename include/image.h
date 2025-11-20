#include <span>
#include <cstdint>
#include <matrix.h>

class Image : Matrix2D<uint8_t> {

public:
  /**
   * Connected Component Labeling
   * Detect islands in the image. Islands are separated with background
   * (ignored_value).
   *
   * @param ignored_value
   * @return matrix with labels
   */
    Matrix2D connected_component_labeling(uint8_t ignored_value);

};
