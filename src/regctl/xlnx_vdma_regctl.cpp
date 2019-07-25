#include "xlnx_vdma_regctl.h"



/* offsetister/Descriptor Offsets */
#define XILINX_DMA_MM2S_CTRL_OFFSET		0x0000
#define XILINX_DMA_S2MM_CTRL_OFFSET		0x0030
#define XILINX_VDMA_MM2S_DESC_OFFSET		0x0050
#define XILINX_VDMA_S2MM_DESC_OFFSET		0x00a0

/* Control offsetisters */
#define XILINX_DMA_REG_DMACR			0x0000
#define XILINX_DMA_DMACR_DELAY_MAX		0xff
#define XILINX_DMA_DMACR_DELAY_SHIFT		24
#define XILINX_DMA_DMACR_FRAME_COUNT_MAX	0xff
#define XILINX_DMA_DMACR_FRAME_COUNT_SHIFT	16
#define XILINX_DMA_DMACR_ERR_IRQ		BIT(14)
#define XILINX_DMA_DMACR_DLY_CNT_IRQ		BIT(13)
#define XILINX_DMA_DMACR_FRM_CNT_IRQ		BIT(12)
#define XILINX_DMA_DMACR_MASTER_SHIFT		8
#define XILINX_DMA_DMACR_FSYNCSRC_SHIFT	5
#define XILINX_DMA_DMACR_FRAMECNT_EN		BIT(4)
#define XILINX_DMA_DMACR_GENLOCK_EN		BIT(3)
#define XILINX_DMA_DMACR_RESET			BIT(2)
#define XILINX_DMA_DMACR_CIRC_EN		BIT(1)
#define XILINX_DMA_DMACR_RUNSTOP		BIT(0)
#define XILINX_DMA_DMACR_FSYNCSRC_MASK		GENMASK(6, 5)

#define XILINX_DMA_REG_DMASR			0x0004
#define XILINX_DMA_DMASR_EOL_LATE_ERR		BIT(15)
#define XILINX_DMA_DMASR_ERR_IRQ		BIT(14)
#define XILINX_DMA_DMASR_DLY_CNT_IRQ		BIT(13)
#define XILINX_DMA_DMASR_FRM_CNT_IRQ		BIT(12)
#define XILINX_DMA_DMASR_SOF_LATE_ERR		BIT(11)
#define XILINX_DMA_DMASR_SG_DEC_ERR		BIT(10)
#define XILINX_DMA_DMASR_SG_SLV_ERR		BIT(9)
#define XILINX_DMA_DMASR_EOF_EARLY_ERR		BIT(8)
#define XILINX_DMA_DMASR_SOF_EARLY_ERR		BIT(7)
#define XILINX_DMA_DMASR_DMA_DEC_ERR		BIT(6)
#define XILINX_DMA_DMASR_DMA_SLAVE_ERR		BIT(5)
#define XILINX_DMA_DMASR_DMA_INT_ERR		BIT(4)
#define XILINX_DMA_DMASR_IDLE			BIT(1)
#define XILINX_DMA_DMASR_HALTED		BIT(0)
#define XILINX_DMA_DMASR_DELAY_MASK		GENMASK(31, 24)
#define XILINX_DMA_DMASR_FRAME_COUNT_MASK	GENMASK(23, 16)

#define XILINX_DMA_REG_CURDESC			0x0008
#define XILINX_DMA_REG_TAILDESC		0x0010
#define XILINX_DMA_REG_offset_INDEX		0x0014
#define XILINX_DMA_REG_FRMSTORE		0x0018
#define XILINX_DMA_REG_THRESHOLD		0x001c
#define XILINX_DMA_REG_FRMPTR_STS		0x0024
#define XILINX_DMA_REG_PARK_PTR		0x0028
#define XILINX_DMA_PARK_PTR_WR_REF_SHIFT	8
#define XILINX_DMA_PARK_PTR_WR_REF_MASK		GENMASK(12, 8)
#define XILINX_DMA_PARK_PTR_RD_REF_SHIFT	0
#define XILINX_DMA_PARK_PTR_RD_REF_MASK		GENMASK(4, 0)
#define XILINX_DMA_REG_VDMA_VERSION		0x002c

/* offsetister Direct Mode offsetisters */
#define XILINX_DMA_REG_VSIZE			0x0000
#define XILINX_DMA_REG_HSIZE			0x0004

#define XILINX_DMA_REG_FRMDLY_STRIDE		0x0008
#define XILINX_DMA_FRMDLY_STRIDE_FRMDLY_SHIFT	24
#define XILINX_DMA_FRMDLY_STRIDE_STRIDE_SHIFT	0

#define XILINX_VDMA_REG_START_ADDRESS(n)	(0x000c + 4 * (n))
#define XILINX_VDMA_REG_START_ADDRESS_64(n)	(0x000c + 8 * (n))

/* HW specific definitions */
#define XILINX_DMA_MAX_CHANS_PER_DEVICE	0x20

#define XILINX_DMA_DMAXR_ALL_IRQ_MASK	\
		(XILINX_DMA_DMASR_FRM_CNT_IRQ | \
		 XILINX_DMA_DMASR_DLY_CNT_IRQ | \
		 XILINX_DMA_DMASR_ERR_IRQ)

#define XILINX_DMA_DMASR_ALL_ERR_MASK	\
		(XILINX_DMA_DMASR_EOL_LATE_ERR | \
		 XILINX_DMA_DMASR_SOF_LATE_ERR | \
		 XILINX_DMA_DMASR_SG_DEC_ERR | \
		 XILINX_DMA_DMASR_SG_SLV_ERR | \
		 XILINX_DMA_DMASR_EOF_EARLY_ERR | \
		 XILINX_DMA_DMASR_SOF_EARLY_ERR | \
		 XILINX_DMA_DMASR_DMA_DEC_ERR | \
		 XILINX_DMA_DMASR_DMA_SLAVE_ERR | \
		 XILINX_DMA_DMASR_DMA_INT_ERR)
		 
		 
		 




xlnx_vdma_regctl::xlnx_vdma_regctl(struct uio_info_t* info, int map)
{
	info_ = info;
	map_ = map;
}

int xlnx_vdma_regctl::set_soft_reset()
{
	int ret;
	ret = uio_set32(info_, map_, ctrl_offset(0, XILINX_DMA_REG_DMACR), XILINX_DMA_DMACR_RESET);
	if (ret < 0)
		return -1;
	
	ret = uio_set32(info_, map_, ctrl_offset(1, XILINX_DMA_REG_DMACR), XILINX_DMA_DMACR_RESET);
	if (ret < 0)
		return -1;
	
	return 0;
}

int xlnx_vdma_regctl::set_vdma_channel_sample(u32 ddr_base, u32 width, u32 height, u32 bpp, u32 chan)
{
	int ret;
	u32 reg = 0;
	ret = uio_read32(info_, map_, ctrl_offset(chan, XILINX_DMA_REG_DMACR), &reg);
	if (ret < 0)
		return -1;
	reg |= XILINX_DMA_DMAXR_ALL_IRQ_MASK;
	reg |= XILINX_DMA_DMACR_FRM_CNT_IRQ;
	reg |= XILINX_DMA_DMACR_CIRC_EN;
	reg |= XILINX_DMA_DMACR_RUNSTOP;
	ret = uio_write32(info_, map_, ctrl_offset(chan, XILINX_DMA_REG_DMACR), reg);
	if (ret < 0)
		return -1;
	
	ret = uio_write32(info_, map_, desc_offset(chan, XILINX_VDMA_REG_START_ADDRESS(0)), ddr_base);
	if (ret < 0)
		return -1;
	
	ret = uio_write32(info_, map_, desc_offset(chan, XILINX_DMA_REG_HSIZE), width * bpp);
	if (ret < 0)
		return -1;
	
	ret = uio_write32(info_, map_, desc_offset(chan, XILINX_DMA_REG_FRMDLY_STRIDE), width * bpp);
	if (ret < 0)
		return -1;
	
	ret = uio_write32(info_, map_, desc_offset(chan, XILINX_DMA_REG_VSIZE), height);
	if (ret < 0)
		return -1;
	
	return 0;
}

int xlnx_vdma_regctl::clear_irq_mask()
{
	int ret;
	u32 reg = 0;
	ret = uio_read32(info_, map_, ctrl_offset(0, XILINX_DMA_REG_DMASR), &reg);
	if (ret < 0)
		return -1;
	reg = reg & XILINX_DMA_DMAXR_ALL_IRQ_MASK;
	ret = uio_write32(info_, map_, ctrl_offset(0, XILINX_DMA_REG_DMASR), reg);
	if (ret < 0)
		return -1;
	ret = uio_read32(info_, map_, ctrl_offset(1, XILINX_DMA_REG_DMASR), &reg);
	if (ret < 0)
		return -1;
	reg = reg & XILINX_DMA_DMAXR_ALL_IRQ_MASK;
	ret = uio_write32(info_, map_, ctrl_offset(1, XILINX_DMA_REG_DMASR), reg);
	if (ret < 0)
		return -1;
	
	return 0;
}

u32 xlnx_vdma_regctl::ctrl_offset(u32 chan, u32 offset)
{
	u32 reg = (chan == 0) ? XILINX_DMA_S2MM_CTRL_OFFSET : XILINX_DMA_MM2S_CTRL_OFFSET;
	return (reg + offset);
}


u32 xlnx_vdma_regctl::desc_offset(u32 chan, u32 offset)
{
	u32 reg = (chan == 0) ? XILINX_VDMA_S2MM_DESC_OFFSET : XILINX_VDMA_MM2S_DESC_OFFSET;
	return (reg + offset);
}




