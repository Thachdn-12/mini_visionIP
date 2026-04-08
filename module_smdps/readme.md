## INPUT
    vector field from UFM
## OUPUT
    vector field smooth + reliable + edge-aware

## Main Task:
    1. Remove outlier
        - Wrong vector (by occlusion, noise, bad texture)
        - Base on:
            - Abnormal magnitude
            - Direction is off-center compared to neighbor
    2. Spatial smoothing (edge-aware)
        - Smooths the surface without blurring the object boundary
        - Used:
            - Bilateral filter
            - Guided filter
    3. Consistency check
        - Check:
            - Forward–Backward consistency
            - Local coherence


Pipeline:
            Input Flow
               ↓
        Outlier Detection
               ↓
        Mask invalid vectors
               ↓
        Edge-aware smoothing
               ↓
        Consistency refinement
               ↓
        Output Refined Flow