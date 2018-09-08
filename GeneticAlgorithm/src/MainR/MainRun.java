/**   
 * Copyright © 2018 liao. All rights reserved.
 * 
 *	Life is but a span
 * @Package: MainR 
 * @author: Administrator   
 * @date: 2018年9月7日 下午3:43:12 
 */
package MainR;

import TSP.GeneticAlgorithm;
import TSP.SpeciesPopulation;
import TSP.Specieslndividual;

/**
 * @date: 2018年9月7日 下午3:43:12
 * @episode : 
 */
public class MainRun {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//创建遗传算法驱动对象
		GeneticAlgorithm GA = new GeneticAlgorithm();
		
		//创建初始种群
		SpeciesPopulation SP = new SpeciesPopulation();
		
		//开始遗传算法（选择算子、交叉算子、变异算子）
		Specieslndividual bestTate = GA.run(SP);
		
		//打印路径与最短距离
		bestTate.printRate();
	}

}
