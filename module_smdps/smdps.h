#pragma once

#include "../module_ufm/ufm_types.h"

class SMDPS {
    public:
        SMDPS();
    
        void process(const std::vector<std::vector<uint8_t>>& gray,
                     const FlowField& flow_in,
                     FlowField& flow_out);
        
    private:
        int width;
        int height;
        
        float thresh_mag;
        int radius;
        float sigma_s;
        float sigma_c;
        
        std::vector<std::vector<int>> valid_mask;
        
        void compute_outlier_mask(const FlowField& flow);
        void smooth(const std::vector<std::vector<uint8_t>>& gray,
                    const FlowField& flow,
                    FlowField& out);
        void consistency(FlowField& flow);
};