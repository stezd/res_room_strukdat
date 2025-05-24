#include "Reservation.hpp"

Reservation::Reservation(const std::string &id, const std::string &nama, const std::string &nim,
                         const std::string &ruangan, const std::string &tanggal, const std::string &jamMulai,
                         const std::string &jamSelesai,
                         const std::string &status)
    : id(id), nama(nama), nim(nim), ruangan(ruangan), tanggal(tanggal),
      jamMulai(jamMulai), jamSelesai(jamSelesai), status(status) {
}

Reservation Reservation::from_json(const nlohmann::json &j) {
    try {
        Reservation r;
        r.setId(j.at("id").get<std::string>());
        r.setNama(j.at("nama").get<std::string>());
        r.setNim(j.at("nim").get<std::string>());
        r.setRuangan(j.at("ruangan").get<std::string>());
        r.setTanggal(j.at("tanggal").get<std::string>());
        r.setJamMulai(j.at("jamMulai").get<std::string>());
        r.setJamSelesai(j.at("jamSelesai").get<std::string>());
        r.setStatus(j.at("status").get<std::string>());
        return r;
    } catch (const nlohmann::json::exception &e) {
        throw std::runtime_error("Failed to parse JSON: " + std::string(e.what()));
    }
}

nlohmann::json Reservation::to_json() const {
    nlohmann::json j;
    try {
        j = {
            {"id", id},
            {"nama", nama},
            {"nim", nim},
            {"ruangan", ruangan},
            {"tanggal", tanggal},
            {"jamMulai", jamMulai},
            {"jamSelesai", jamSelesai},
            {"status", status}
        };
        return j;
    } catch (const nlohmann::json::exception &e) {
        throw std::runtime_error("Failed to create JSON: " + std::string(e.what()));
    }
}
