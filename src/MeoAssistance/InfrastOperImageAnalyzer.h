#pragma once
#include "AbstractImageAnalyzer.h"

#include "AsstInfrastDef.h"

namespace asst
{
    class InfrastOperImageAnalyzer : public AbstractImageAnalyzer
    {
    public:
        enum ToBeCalced
        {
            None = 0,
            Smiley = 0b1,
            Mood = 0b10,
            Hash = 0b100,
            Skill = 0b1000,
            Selected = 0b10000,
            Doing = 0b100000,
            All = 0b111111
        };

        using AbstractImageAnalyzer::AbstractImageAnalyzer;
        virtual ~InfrastOperImageAnalyzer() = default;
        InfrastOperImageAnalyzer(const cv::Mat& image, const Rect& roi) = delete;

        virtual bool analyze() override;

        void sort_by_loc();
        void sort_by_mood();

        auto get_result() const noexcept -> const std::vector<infrast::Oper>&
        {
            return m_result;
        }
        void set_facility(std::string facility) noexcept
        {
            m_facility = std::move(facility);
        }
        void set_to_be_calced(int to_be_calced) noexcept
        {
            m_to_be_calced = to_be_calced;
        }

        constexpr static int MaxNumOfSkills = 2; // 单个干员最多有几个基建技能

    private:
        // 该分析器不支持外部设置ROI
        virtual void set_roi(const Rect& roi) noexcept override
        {
            AbstractImageAnalyzer::set_roi(roi);
        }
        virtual void set_image(const cv::Mat& image, const Rect& roi)
        {
            AbstractImageAnalyzer::set_image(image, roi);
        }

        void oper_detect();
        void mood_analyze();
        void hash_analyze();
        void skill_analyze();
        void selected_analyze();
        void doing_analyze();

        std::string m_facility;
        std::vector<infrast::Oper> m_result;
        int m_to_be_calced = All;
    };
}