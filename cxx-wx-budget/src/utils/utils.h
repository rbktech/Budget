#pragma once

#include <valarray>
#include <wx/string.h>

class CUtils
{

public:
    static wxString formatMoney(const double& dValue)
    {
        wxString result;

        double max = std::pow(2, 32) - 1;
        if(dValue > max)
            return result;

        uint32_t iValue = static_cast<uint32_t>(dValue);

        result = wxString::Format(wxT(".%i ₽"), uint32_t((dValue - iValue) * 100));

        while(iValue != 0) {

            uint32_t res = iValue % 1000;

            if(res < 10 && iValue > 1000)
                result.Prepend(wxString::Format(wxT("00%i"), res));
            else if(res < 100 && iValue > 1000)
                result.Prepend(wxString::Format(wxT("0%i"), res));
            else
                result.Prepend(wxString::Format(wxT("%i"), res));

            if((iValue /= 1000) != 0)
                result.Prepend(wxT(' '));
        }

        return result;
    }

    static double annuity(const double& body, const double& interest_rate, const double& count_month)
    {
        double annuity = 0.0;

        // double interest_rate = 5.00;
        // double count_month = 360.0;
        // double body = 8 000 000.0;

        const double pc = interest_rate / 12 / 100;

        annuity = (pc / (1 - std::pow(1 + pc, -count_month))) * body;

        // double a = (1 - 1 / std::pow(1 + pc, count_month - 1 + 1)) * annuity;
        // double b = annuity / std::pow(1 + pc, count_month - 1 + 1);

        return annuity;
    }

    static double percent_month(const double& annuity,
        const double& interest_rate,
        const double& count_month,
        const double& num_month)
    {
        double result = 0.0;

        double pc = interest_rate / 12 / 100;

        result = (1 - 1 / std::pow(1 + pc, count_month - num_month + 1)) * annuity;

        return result;
    }

    static double
    body_month(const double& annuity, const double& interest_rate, const double& count_month, const double& num_month)
    {
        double result = 0.0;

        const double pc = interest_rate / 12 / 100;

        result = annuity / std::pow(1 + pc, count_month - num_month + 1);

        return result;
    }

    CUtils() = default;
    ~CUtils() = default;
};
