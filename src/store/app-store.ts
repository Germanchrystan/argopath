import { create } from 'zustand'
import type { ReactElement } from 'react'

type AppStore = {
  wasmLoaded: boolean
  modal: ReactElement | null
  setWasmLoaded: (loaded: boolean) => void
  setModal: (modal: ReactElement | null) => void
}

export const useAppStore = create<AppStore>((set) => ({
  wasmLoaded: false,
  modal: null,
  setWasmLoaded: (loaded) => set({ wasmLoaded: loaded }),
  setModal: (modal) => set({ modal }),
}))
