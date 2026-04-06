[Video Input] → [ISP] → [UFM Optical Flow] → [Vector Field Output]

## INPUT
    Frame_t (current)
    Frame_t-1 (previous)
## OUTPUT
    vector field: flow(x, y) = (vx, vy)

          +----------------------+
frame_t → |                      |
          |                      |
          |   Optical Flow Core  | → flow(x,y) = (vx, vy)
          |                      |
frame_t-1 →                      |
          +----------------------+