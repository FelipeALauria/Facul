package DAO;

import DTO.FuncionarioCinemaDTO;

/**
 *
 * @author felip
 */
public class FuncionarioCinemaDAO extends FuncionarioDAO {

    public double adicionalDePericulosidade(FuncionarioCinemaDTO funcionario) {
        double adicional = (funcionario.getCargaHoraria() * funcionario.getSalarioHora()) * 1.3;
        return adicional;
    }

}
